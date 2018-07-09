/* Program to show how to access the io details from a user space program */
/* Program must be run as a root user */
#include <stdio.h>
#include <stdint.h>
#include <sys/io.h>

/* RTC is DS 12887 and it is a Port Mapped Device */

/* Address of RTC Registers */
#define ADDRESS_REG	0x70
#define DATA_REG	0x71

/* Values/Commands for RTC Registers */
#define SECOND		0x00	//Second      00-59
#define MINUTE		0x02	//Minute      00-59
#define HOUR		0x04	//Hour        00-23
#define DAY_OF_WEEK	0x06	//Day of Week 01-0DAY
#define DAY		0x07	//Day         00-31
#define MONTH		0x08	//Month       00-12
#define YEAR		0x09	//Year        00-99

/* RTC Register Address Offset w.r.t Base Address */
#define PERM_RANGE	0x02

/* Enable/Disable the Application to Access I/O Port */
#define PERM_ENABLE	0x01
#define PERM_DISABLE	0x00

/* Function to Get any RTC Parameter */
uint8_t get_RTC_val(uint8_t param)
{
  outb(param, ADDRESS_REG);
  return inb(DATA_REG);
}

/* Function to Set any RTC Parameter */
void set_RTC_val(uint8_t param, uint8_t setVal)
{
   outb(param, ADDRESS_REG);
   outb(setVal, DATA_REG);
}

int main(void)
{
  /* Obtain Permission to Access Port from Userspace */
  if(0 != ioperm(ADDRESS_REG, PERM_RANGE, PERM_ENABLE))
  {
    perror("IOPERM : ");
    return -1;
  }
  printf("Port Permission Granted\n");

  /* Printing in user friendly format */
  /* Gives GMT , to convert to local time zone we need to add/subtract */
  printf("%02x:",get_RTC_val(HOUR));
  printf("%02x:",get_RTC_val(MINUTE));
  printf("%02x,",get_RTC_val(SECOND));
  printf("%02x/",get_RTC_val(DAY));
  printf("%02x/",get_RTC_val(MONTH));
  printf("%02x\n",get_RTC_val(YEAR));

  return 0;
}

