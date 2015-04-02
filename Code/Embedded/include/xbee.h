#ifndef XBEE_H
#define	XBEE_H

/// @file

extern void init_xbee(void);
extern bool is_xbee_on(void);
extern int write_xbee(void *buffer, unsigned int len);
extern int read_xbee(void *buffer, unsigned int len);

#endif /* XBEE_H */
