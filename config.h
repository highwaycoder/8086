#ifndef CONFIG_H
#define CONFIG_H

#define USAGE "Usage: 8086 floppy_image\n\
Where \"floppy_image\" is the file you want to boot from.\n"

extern char BUILD_DATE;
extern char BUILD_NUMBER;

#define print_copyright() printf("8086 Version %.2f © Chris Browne 2011-2012.  Build on %u.  Build no.: %04u\n",VERSION,(unsigned long) &BUILD_DATE, (unsigned long) &BUILD_NUMBER)

#endif
