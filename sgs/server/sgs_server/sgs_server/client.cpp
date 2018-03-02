#include "client.h"
#include "app.h"
#include "player.h"
#include "game.h"


Client::Client(Player* p):m_pPlayer(p)
{

}


Client::~Client()
{
	if(-1 != m_nfd)
	{
		ev_io_stop(g_app.m_pLoop, &m_ev_read);
		ev_io_stop(g_app.m_pLoop, &m_ev_write);
		close(m_nfd);
		m_nfd = -1;
	}
}

int Client::Active()
{
	m_ev_read.data = this;
	m_ev_write.data = this;
	ev_io_init(&m_ev_read, Client::Read_cb, m_nfd, EV_READ);
	ev_io_start(g_app.m_pLoop, &m_ev_read);

	ev_io_init(&m_ev_write, Client::Write_cb, m_nfd, EV_WRITE);
	return 0;
}

void Client::Read_cb(struct ev_loop * loop, ev_io * w, int revents)
{
	Client* self = (Client*)w->data;

	/* recv header*/
	int   len;
	if (STAT_HEADER == self->m_iPacket.status())
	{
		len = sizeof(PHeader);
	}
	/*recv body*/
	else
	{
		len = self->m_iPacket.header().len;
	}

	int nRet = read(self->m_nfd, self->m_pRecvBuf, len - self->m_iPacket.curlen());
	if (nRet > 0)
	{
		bool bEnd = false;
		if (STAT_HEADER == self->m_iPacket.status())
		{
			/*recv header*/
			memcpy((char*)&self->m_iPacket.header() + self->m_iPacket.curlen(), 
				self->m_pRecvBuf, nRet);
			self->m_iPacket.curlen() += nRet;
			if (self->m_iPacket.curlen() == len)
			{
				self->m_iPacket.save();
				self->m_iPacket.curlen() = 0;
				if (self->m_iPacket.header().len == 0)
				{
					self->m_iPacket.status() = STAT_END;
					bEnd = true;
				}
				else if (self->m_iPacket.header().len <= MAX_RECV_BUF_SIZE)
				{
					self->m_iPacket.status() = STAT_BODY;
				}
				else{
					//err
				}
			}
		}
		else if (STAT_BODY == self->m_iPacket.status())
		{
			/* recv body*/
			if(self->m_iPacket.header().len > 0)
			{
				self->m_iPacket.body().append(self->m_pRecvBuf, nRet);
				self->m_iPacket.curlen() += nRet;
				if (len == self->m_iPacket.curlen())
				{
					sgslog.info(FFL_s_s, "recv:", self->m_iPacket.body().c_str());
					self->m_iPacket.status() = STAT_END;
					bEnd = true;
				}
			}
		}
		if (bEnd)
		{
			//to do
			int start = time(NULL);
			do 
			{
				if (g_app.m_pGame->BeforeDo(self->m_pPlayer) < 0)
				{
					sgslog.error(FFL_s, "before err!");
					break;
				}
				if (g_app.m_pGame->Do(self->m_pPlayer) < 0)
				{
					sgslog.error(FFL_s, "do err!");
					break;
				}

				if (g_app.m_pGame->AfterDo(self->m_pPlayer) < 0)
				{
					sgslog.error(FFL_s, "after err!");
					break;
				}
			} while (0);

			if (time(NULL) - start > 1)
			{
				sgslog.warn(FFL_s_u, "slow cmd:", self->m_iPacket.header().cmd);
			}

		}
	}
	else if (0 == nRet)
	{
		sgslog.warn(FFL_s, "fd closed!");
		//destory
		g_app.m_pGame->ReqUserQuit(self->m_pPlayer);
	}
	else
	{
		if (!(errno == EAGAIN || errno == EINPROGRESS || errno == EINTR || errno == EWOULDBLOCK))
		{
			sgslog.warn(FFL_s, strerror(errno));
			//destory
			g_app.m_pGame->ReqUserQuit(self->m_pPlayer);
		}
	}
	return;
}

void Client::Write_cb(struct ev_loop * loop, ev_io * w, int revents)
{
	Client *self = (Client*)w->data;
	if (self->m_lstWrite.empty()) {
		//sgslog.debug("stop write event\n");
		ev_io_stop(EV_A_ w);
		return;
	}
	PPacket& pkt = self->m_lstWrite.front();	

	size_t written = write(self->m_nfd, pkt.data().c_str() + pkt.curlen(), pkt.data().length() - pkt.curlen());
	
	
	sgslog.info(FFL_d_d_d_d_s, self->m_nfd, pkt.header().cmd, pkt.data().length(),written, pkt.data().c_str() + sizeof(PHeader));

	
	if (written < 0) {
		if (errno == EAGAIN || errno == EINPROGRESS || errno == EINTR) {
			sgslog.warn(FFL_s_s,"write failed", strerror(errno));
			return;
		}
		/* todo close this client */
		sgslog.error(FFL_s_d, "unknow err in written:\n", self->m_nfd);
		g_app.m_pGame->ReqUserQuit(self->m_pPlayer);
		return;
	}
	else if(0 == written)
	{
		sgslog.warn(FFL_s, "fd closed!");
		g_app.m_pGame->ReqUserQuit(self->m_pPlayer);
	}

	pkt.curlen() += written;
	if ((std::size_t)pkt.curlen() == pkt.data().length())
	{
		self->m_lstWrite.pop_front();
	}
	return;
}
