#ifndef PIC2PIC_H
#define	PIC2PIC_H

/// @file

extern bool is_pic2pic_on(void);
extern void init_pic2pic(void);
extern int write_pic2pic(void *buffer, unsigned int len);
extern int read_pic2pic(void *buffer, unsigned int len);

#endif /* PIC2PIC_H */
