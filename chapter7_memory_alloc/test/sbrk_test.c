#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
extern char end;
int main()
{
		printf("sizeof(int)=%ld, sizeof(int *)=%ld\n", sizeof(int),sizeof(int *));
		printf("init:sbrk(0)=%p, end=%p\n", sbrk(0), &end);
		void *p = sbrk(32);
		printf("after:sbrk(32)= %p, %p\n", p,sbrk(0));
		void *p1 = sbrk(32);
		printf("p1=%p, %p\n", p1,sbrk(0));
		void *p2 = sbrk(-32);
		printf("p2 = %p, sbrk(0) = %p\n", p2, sbrk(0));
		void *p3 = sbrk(-32);
		printf("p33=%p, sbrk(0)= %p\n", p3 , sbrk(0));
		p = malloc(24);
		int ii;
		for(ii = 0; ii < 25; ii++)
			*((char *)p+ii) = 0xFF;
		printf("malloc(1) = %p, sbrk(0)= %p\n", p, sbrk(0));
		//*((char *)p) = 10;
		int *a = (int *)((char *)p - 16);
		printf("a = %d, %p\n", *a, a);
		int *b = (int *)((char *)p - 12);
		printf("b = %d, %p\n", *b, b);
		int *c = (int *)((char *)p - 8);
		printf("c = %d, %p\n", *c, c);
		int *d = (int *)((char *)p - 4);
		printf("d = %d, %p\n", *d, d);
		int *e =  (int *)((char *)p);
		printf("e = %d, %p\n", *e, e);
		int *f =  (int *)((char *)p+4);
		printf("f = %d, %p\n", *f, f);
		int *g =  (int *)((char *)p+8);
		printf("g = %d, %p\n", *g, g);
		int *h =  (int *)((char *)p+12);
		printf("h = %d, %p\n", *h, h);
		int *i=  (int *)((char *)p+16);
		printf("i = %d, %p\n", *i, i);
		int *j=  (int *)((char *)p+20);
		printf("j = %d, %p\n", *j, j);
		int *k=  (int *)((char *)p+24);
		printf("k = %d, %p\n", *k, k);
		
		char *freep1 = p;
		p = malloc(1);
		printf("malloc1(1) = %p, sbrk(0)= %p\n", p, sbrk(0));
		a = (int *)((char *)p - 16);
		printf("a1 = %d, %p\n", *a, a);
		b = (int *)((char *)p - 12);
		printf("b1 = %d, %p\n", *b, b);
		c = (int *)((char *)p - 8);
		printf("c1 = %d, %p\n", *c, c);
		d = (int *)((char *)p - 4);
		printf("d1 = %d, %p\n", *d, d);
		
		char *tmp = p;
		p = malloc(1);
		printf("malloc2(1) = %p, sbrk(0)= %p\n", p, sbrk(0));
		a = (int *)((char *)p - 16);
		printf("a2 = %d, %p\n", *a, a);
		b = (int *)((char *)p - 12);
		printf("b2 = %d, %p\n", *b, b);
		c = (int *)((char *)p - 8);
		printf("c2 = %d, %p\n", *c, c);
		d = (int *)((char *)p - 4);
		printf("d2 = %d, %p\n", *d, d);	
		e =  (int *)((char *)p);
		printf("e2 = %d, %p\n", *e, e);
		f =  (int *)((char *)p+4);
		printf("f2 = %d, %p\n", *f, f);
		g =  (int *)((char *)p+8);
		printf("g2= %d, %p\n", *g, g);
		h =  (int *)((char *)p+12);
		printf("h2 = %d, %p\n", *h, h);
		i=  (int *)((char *)p+16);
		printf("i2 = %d, %p\n", *i, i);
		char *freep2= p;
		p = malloc(1);
		printf("malloc3(1) = %p, sbrk(0)= %p\n", p, sbrk(0));
		a = (int *)((char *)p - 16);
		printf("a3 = %d, %p\n", *a, a);
		b = (int *)((char *)p - 12);
		printf("b3 = %d, %p\n", *b, b);
		c = (int *)((char *)p - 8);
		printf("c3 = %d, %p\n", *c, c);
		d = (int *)((char *)p - 4);
		printf("d3 = %d, %p\n", *d, d);	
		e =  (int *)((char *)p);
		printf("e3 = %d, %p\n", *e, e);
		f =  (int *)((char *)p+4);
		printf("f3 = %d, %p\n", *f, f);
		g =  (int *)((char *)p+8);
		printf("g3= %d, %p\n", *g, g);
		h =  (int *)((char *)p+12);
		printf("h3 = %d, %p\n", *h, h);
		i=  (int *)((char *)p+16);
		printf("i3 = %d, %p\n", *i, i);
		
		p = malloc(1);
		printf("malloc4(1) = %p, sbrk(0)= %p\n", p, sbrk(0));
		char *freep3 = p;
		p = malloc(1);
		printf("malloc5(1) = %p, sbrk(0)= %p\n", p, sbrk(0));
		free(freep1);
		free(freep2);
		free(freep3);
		p = freep1;
		printf("free(1) = %p, sbrk(0)= %p\n", p, sbrk(0));
		a = (int *)((char *)p - 16);
		printf("a4 = %d, %p\n", *a, a);
		b = (int *)((char *)p - 12);
		printf("b4 = %d, %p\n", *b, b);
		c = (int *)((char *)p - 8);
		printf("c4 = %d, %p\n", *c, c);
		d = (int *)((char *)p - 4);
		printf("d4 = %d, %p\n", *d, d);	
		e =  (int *)((char *)p);
		printf("e4 = %d, %p\n", *e, e);
		f =  (int *)((char *)p+4);
		printf("f4 = %d, %p\n", *f, f);
		g =  (int *)((char *)p+8);
		printf("g4= %d, %p\n", *g, g);
		h =  (int *)((char *)p+12);
		printf("h4 = %d, %p\n", *h, h);
		i=  (int *)((char *)p+16);
		printf("i4 = %d, %p\n", *i, i);
		
		p = freep2;
		printf("free(2) = %p, sbrk(0)= %p\n", p, sbrk(0));
		a = (int *)((char *)p - 16);
		printf("a5 = %d, %p\n", *a, a);
		b = (int *)((char *)p - 12);
		printf("b5 = %d, %p\n", *b, b);
		c = (int *)((char *)p - 8);
		printf("c5 = %d, %p\n", *c, c);
		d = (int *)((char *)p - 4);
		printf("d5 = %d, %p\n", *d, d);	
		e =  (int *)((char *)p);
		printf("e5 = %x, %p\n", *e, e);
		f =  (int *)((char *)p+4);
		printf("f5 = %d, %p\n", *f, f);
		g =  (int *)((char *)p+8);
		printf("g5= %d, %p\n", *g, g);
		h =  (int *)((char *)p+12);
		printf("h5 = %d, %p\n", *h, h);
		i=  (int *)((char *)p+16);
		printf("i5 = %d, %p\n", *i, i);
		
		p = freep3;
		printf("free(3) = %p, sbrk(0)= %p\n", p, sbrk(0));
		a = (int *)((char *)p - 16);
		printf("a6 = %d, %p\n", *a, a);
		b = (int *)((char *)p - 12);
		printf("b6 = %d, %p\n", *b, b);
		c = (int *)((char *)p - 8);
		printf("c6 = %d, %p\n", *c, c);
		d = (int *)((char *)p - 4);
		printf("d6 = %d, %p\n", *d, d);	
		e =  (int *)((char *)p);
		printf("e6 = %x, %p\n", *e, e);
		f =  (int *)((char *)p+4);
		printf("f6 = %d, %p\n", *f, f);
		g =  (int *)((char *)p+8);
		printf("g6= %d, %p\n", *g, g);
		h =  (int *)((char *)p+12);
		printf("h6 = %d, %p\n", *h, h);
		i=  (int *)((char *)p+16);
		printf("i6 = %d, %p\n", *i, i);
		
		
		
}
