/* Program to access CMOS RTC from Kernel Space */
#include <linux/init.h>
#include <linux/module.h>
#include <asm/io.h>

/* RTC is DS 12887 and it is a Port Mapped Device */

/* We dont need access permission like userspace (ioperm) */
/* This is because we are already in kernelspace */
/* We can directly use the IN/OUT instructions for Port Mapped IO */

/* Address of RTC Registers */
#define ADDRESS_REG     0x70
#define DATA_REG        0x71

/* Values/Commands for RTC Registers */
#define SECOND          0x00    //Second      00-59
#define MINUTE          0x02    //Minute      00-59
#define HOUR            0x04    //Hour        00-23
#define DAY_OF_WEEK     0x06    //Day of Week 01-0DAY
#define DAY             0x07    //Day         00-31
#define MONTH           0x08    //Month       00-12
#define YEAR            0x09    //Year        00-99

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

/* Entry Function */
int init_module(void)
{
  printk("%s\n",__func__);

  /* Printing in user friendly format */
  /* Gives GMT , to convert to local time zone we need to add/subtract */
  pr_info("%02x:%02x:%02x, %02x/%02x/%02x\r\n", get_RTC_val(HOUR), get_RTC_val(MINUTE), 
    get_RTC_val(SECOND), get_RTC_val(DAY), get_RTC_val(MONTH), get_RTC_val(YEAR));

  return 0;
}

/* Exit Function */
void cleanup_module(void)
{
  printk("%s\n",__func__);
}

/* Comments which are retained in code */
MODULE_AUTHOR("debmalyasarkar1@gmail.com");
MODULE_DESCRIPTION("Access CMOS RTC Module");
MODULE_LICENSE("GPL");
