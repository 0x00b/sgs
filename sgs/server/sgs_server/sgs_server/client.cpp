#include "client.h"
#include "app.h"
#include "player.h"
#include "game.h"


Client::Client(Player* p):m_pPlayer(p)
{
}


Client::~Client()
{
	ev_io_stop(g_app.m_pLoop, &m_ev_read);
	ev_io_stop(g_app.m_pLoop, &m_ev_write);
	close(m_nfd);
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
	if (STAT_HEADER == self->m_iPacket.m_eStatus)
	{
		len = sizeof(PHeader);
	}
	/*recv body*/
	else
	{
		len = self->m_iPacket.header.len;
	}

	int nRet = read(self->m_nfd, self->m_pRecvBuf, len - self->m_iPacket.m_nCurLen);
	if (nRet > 0)
	{
		bool bEnd = false;
		if (STAT_HEADER == self->m_iPacket.m_eStatus)
		{
			/*recv header*/
			memcpy((char*)&self->m_iPacket.header + self->m_iPacket.m_nCurLen, 
				self->m_pRecvBuf, nRet);
			self->m_iPacket.m_nCurLen += nRet;
			if (self->m_iPacket.m_nCurLen == len)
			{
				self->m_iPacket.save();
				self->m_iPacket.m_nCurLen = 0;
				if (self->m_iPacket.header.len == 0)
				{
					self->m_iPacket.m_eStatus = STAT_END;
					bEnd = true;
				}
				else if (self->m_iPacket.header.len <= MAX_RECV_BUF_SIZE)
				{
					self->m_iPacket.m_eStatus = STAT_BODY;
				}
				else{
					//err
				}
			}
		}
		else if (STAT_BODY == self->m_iPacket.m_eStatus)
		{
			/* recv body*/
			if(self->m_iPacket.header.len > 0)
			{
				self->m_iPacket.body.append(self->m_pRecvBuf, nRet);
				self->m_iPacket.m_nCurLen += nRet;
				if (len == self->m_iPacket.m_nCurLen)
				{
					self->m_iPacket.m_eStatus = STAT_END;
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
				if (self->m_pPlayer->BeforeDo() < 0)
				{
					log.error(FFL_s, "before err!");
					break;
				}
				if (self->m_pPlayer->Do() < 0)
				{
					log.error(FFL_s, "do err!");
					break;
				}

				if (self->m_pPlayer->AfterDo() < 0)
				{
					log.error(FFL_s, "after err!");
					break;
				}
			} while (0);

			if (time(NULL) - start > 1)
			{
				log.warn(FFL_s_u, "slow cmd:", self->m_iPacket.header.cmd);
			}

		}
	}
	else if (0 == nRet)
	{
		log.warn(FFL_s, "fd closed!");
		//destory
		g_app.m_pGame->UserQuit(self->m_pPlayer);
	}
	else
	{
		if (!(errno == EAGAIN || errno == EINPROGRESS || errno == EINTR || errno == EWOULDBLOCK))
		{
			log.warn(FFL_s, strerror(errno));
			//destory
			g_app.m_pGame->UserQuit(self->m_pPlayer);
		}
	}
	return;
}

void Client::Write_cb(struct ev_loop * loop, ev_io * w, int revents)
{
	return;
}
