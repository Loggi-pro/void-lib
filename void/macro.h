#pragma once
#define BIT_CHECK(x,BIT) ((x)&(1<<BIT))					//any position
#define BIT_CHECK_MASK(x,MASK) ((x)&(MASK))					//any position
#define BIT_CHECK_ALLIGNED(x,BIT) ((x &(1<<BIT)) >>BIT) //only 0x00 or 0x01

#define BIT_CHANGED(x1,x2,BIT) ((x1 & (1<<BIT))^(x2 & (1<<BIT)))
#define BIT_CHANGED_SET(Dest,Val,BIT) ((Dest & (1<<BIT))^(Val & (1<<BIT)))//returns 1 if BIT Changed 0->1;

#define BIT_TOGGLE(x,BIT)  (x ^= (1<<BIT))
#define BIT_CLEAR(x,BIT) (x &= ~(1<<BIT))
#define BIT_SET(x,BIT) (x |=(1<<BIT))

#define BIT_CLEAR_MASK(x,MASK) (x &= ~(MASK))
#define BIT_SET_VAL(x,MASK) (x |=(MASK))



#define BIT_SET_MASK(x,Val,Mask) (x = (Val&(Mask))|(x&~(Mask)))
#define BIT_SET_EXCEPT(Dest,Val,Mask) (Dest = (Val &~(Mask))|(Dest &(Mask)))//Set Value, except position in mask(1<<x);




//do once macros
//do once: only_once do_something();
#define ONLY_ONCE \
	static unsigned char UNIQUE(__internal_var) = 1; \
	if (UNIQUE(__internal_var)) if (UNIQUE(__internal_var)--)

//����������� ������ b �������� do_iteration(10) do_something();
#define DO_ITERATION(b) \
	static unsigned char UNIQUE(__internal_var) = 0; \
	if (UNIQUE(__internal_var) < b) if (++UNIQUE(__internal_var))

//����������� ����� b �������� do_after_iteration(10) do_something();
#define DO_AFTER_INTERATION(b) static unsigned char UNIQUE(__internal_var) = 0; \
	if (UNIQUE(__internal_var) < b) ++UNIQUE(__internal_var); else

//����������� ����� ����� ����������
#define DO_BETWEEN_ITERATION(a, b) static unsigned char UNIQUE(__internal_var) = 0;\
	if (UNIQUE(__internal_var) < a) ++UNIQUE(__internal_var); else \
		if (UNIQUE(__internal_var) < b) if (++UNIQUE(__internal_var))
