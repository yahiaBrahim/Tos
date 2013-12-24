/* Not yet Used */
#ifndef _DEBUG_H_
#define _DEBUG_H_
      //#if DEBUG_LEVEL > 0
      #define     DEBUG(arg...)     printf("[DEBUG --> ]: %s\n" , ##arg)
      //#else 
      //#define     DEBUG(arg...)  
      //#endif
#endif


/*
 * Affiche la valeur des n octets a l'adresse indiquee
 */
void dump(uchar* addr, int n)
{
	char c1, c2;
	char *tab = "0123456789ABCDEF";
	
	while(n--) {
		c1 = tab[(*addr & 0xF0)>>4];
		c2 = tab[*addr & 0x0F];
		addr++;
		putcar(c1);
		putcar(c2);
	}
}
