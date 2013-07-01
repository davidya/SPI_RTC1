#line 1 "Init.c"
#line 1 "Init.c"

#line 8 "Init.c"
 

 

 




 
void _do_cinit (void);

extern volatile near unsigned long short TBLPTR;
extern near unsigned FSR0;
extern near char __FPFLAGS;
#line 24 "Init.c"

 
 
extern far rom struct
{
  unsigned short num_init;
  struct _init_entry
  {
    unsigned long from;
    unsigned long to;
    unsigned long size;
  }
  entries[];
}
_cinit;

void _do_cinit (void)
{
  
#line 44 "Init.c"
 
  static short long prom;
  static unsigned short curr_byte;
  static unsigned short curr_entry;
  static short long data_ptr;

  
  TBLPTR = (short long)&_cinit;
  _asm
    movlb data_ptr
    tblrdpostinc
    movf TABLAT, 0, 0
    movwf curr_entry, 1
    tblrdpostinc
    movf TABLAT, 0, 0
    movwf curr_entry+1, 1
  _endasm
    
    
    test:
    _asm
     bnz 3
    tstfsz curr_entry, 1
    bra 1
    _endasm
    goto done;
      
#line 76 "Init.c"
 
      _asm
	 
	tblrdpostinc
	movf TABLAT, 0, 0
	movwf prom, 1
	tblrdpostinc
	movf TABLAT, 0, 0
	movwf prom+1, 1
	tblrdpostinc
	movf TABLAT, 0, 0
	movwf prom+2, 1
	 
	tblrdpostinc
	 
	tblrdpostinc
	movf TABLAT, 0, 0
	movwf FSR0L, 0
	tblrdpostinc
	movf TABLAT, 0, 0
	movwf FSR0H, 0
	 
	tblrdpostinc
	tblrdpostinc
	 
	tblrdpostinc
	movf TABLAT, 0, 0
	movwf curr_byte, 1
	tblrdpostinc
	movf TABLAT, 0, 0
	movwf curr_byte+1, 1
	 
	tblrdpostinc
	tblrdpostinc
      _endasm  
      
      
      
      
#line 117 "Init.c"
 
      data_ptr = TBLPTR;
      
       
      TBLPTR = prom;

       
      _asm
        
	movlb curr_byte
	movf curr_byte, 1, 1
copy_loop:
	bnz 2 
	movf curr_byte + 1, 1, 1
	bz 7 

copy_one_byte:
	tblrdpostinc
	movf TABLAT, 0, 0
	movwf POSTINC0, 0

	
	decf curr_byte, 1, 1
	bc -8 
        decf curr_byte + 1, 1, 1
	bra -7 

done_copying:

      _endasm
       
      TBLPTR = data_ptr;
       
      curr_entry--;
      goto test;
done:
;
}

