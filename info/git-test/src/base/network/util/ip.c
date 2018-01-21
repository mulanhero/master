#include <stdio.h>
#include <stdlib.h>

#include <netdb.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>
#include <sys/ioctl.h>
#include <linux/if.h>


//void getip(){
//	int  MAXINTERFACES=16;
// long ip;
// int fd, intrface, retn = 0;
//  struct ifreq buf[MAXINTERFACES]; ///if.h
//  struct ifconf ifc; ///if.h
// ip = -1;
// if ((fd = socket (AF_INET, SOCK_DGRAM, 0)) >= 0) //socket.h
// {
//   ifc.ifc_len = sizeof(buf);
//   ifc.ifc_buf = (caddr_t) buf;
//   if (!ioctl (fd, SIOCGIFCONF, (char *) &ifc)) //ioctl.h
//  {
//    intrface = ifc.ifc_len / sizeof (struct ifreq);
//   while (intrface-- > 0)
//    {
//     if (!(ioctl (fd, SIOCGIFADDR, (char *) &buf[intrface])))
//     {
//      ip=inet_addr( inet_ntoa( ((struct sockaddr_in*)(&buf[intrface].ifr_addr))->sin_addr) );//types
//      break;
//    }
//
//   }
//
//  }
//   close (fd);
//  }
// return ip;
//}
//union ipu{
// long ip;
// unsigned char ipchar[4];
// };
//
//int main(int argc, char **argv){
// union ipu iptest;
// iptest.ip = getlocalhostip();
// printf("local ip:%x :%3u.%3u.%3u.%3u \n",iptest.ip, iptest.ipchar[0],iptest.ipchar[1],iptest.ipchar[2],iptest.ipchar[3]);
// return 0;
//}


long getlocalhostip(){
  int  MAXINTERFACES=16;
 long ip;
 int fd, intrface, retn = 0;
  struct ifreq buf[MAXINTERFACES]; ///if.h
  struct ifconf ifc; ///if.h
 ip = -1;
 if ((fd = socket (AF_INET, SOCK_DGRAM, 0)) >= 0) //socket.h
 {
   ifc.ifc_len = sizeof(buf);
   ifc.ifc_buf = (caddr_t) buf;
   if (!ioctl (fd, SIOCGIFCONF, (char *) &ifc)) //ioctl.h
  {
    intrface = ifc.ifc_len / sizeof (struct ifreq);
   while (intrface-- > 0)
    {
     if (!(ioctl (fd, SIOCGIFADDR, (char *) &buf[intrface])))
     {
      ip=inet_addr( inet_ntoa( ((struct sockaddr_in*)(&buf[intrface].ifr_addr))->sin_addr) );//types
      break;
    }

   }

  }
   close (fd);
  }
 return ip;
}
union ipu{
 long ip;
 unsigned char ipchar[4];
 };

int main(int argc, char **argv){
 union ipu iptest;
 iptest.ip = getlocalhostip();
 printf("local ip:%x :%3u.%3u.%3u.%3u \n",iptest.ip, iptest.ipchar[0],iptest.ipchar[1],iptest.ipchar[2],iptest.ipchar[3]);
 return 0;
}
