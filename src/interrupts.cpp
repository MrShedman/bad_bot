#include "interrupts.h"

#include <array>

namespace IRQ
{
	static constexpr uint8_t INTERRUPT_SIZE = 64;

	static std::array<Callable*, INTERRUPT_SIZE> c_array;

	static void isr0() {c_array[0]->callback();}
	static void isr1() {c_array[1]->callback();}
	static void isr2() {c_array[2]->callback();}
	static void isr3() {c_array[3]->callback();}
	static void isr4() {c_array[4]->callback();}
	static void isr5() {c_array[5]->callback();}
	static void isr6() {c_array[6]->callback();}
	static void isr7() {c_array[7]->callback();}
	static void isr8() {c_array[8]->callback();}
	static void isr9() {c_array[9]->callback();}
	static void isr10() {c_array[10]->callback();}
	static void isr11() {c_array[11]->callback();}
	static void isr12() {c_array[12]->callback();}
	static void isr13() {c_array[13]->callback();}
	static void isr14() {c_array[14]->callback();}
	static void isr15() {c_array[15]->callback();}
	static void isr16() {c_array[16]->callback();}
	static void isr17() {c_array[17]->callback();}
	static void isr18() {c_array[18]->callback();}
	static void isr19() {c_array[19]->callback();}
	static void isr20() {c_array[20]->callback();}
	static void isr21() {c_array[21]->callback();}
	static void isr22() {c_array[22]->callback();}
	static void isr23() {c_array[23]->callback();}
	static void isr24() {c_array[24]->callback();}
	static void isr25() {c_array[25]->callback();}
	static void isr26() {c_array[26]->callback();}
	static void isr27() {c_array[27]->callback();}
	static void isr28() {c_array[28]->callback();}
	static void isr29() {c_array[29]->callback();}
	static void isr30() {c_array[30]->callback();}
	static void isr31() {c_array[31]->callback();}
	static void isr32() {c_array[32]->callback();}
	static void isr33() {c_array[33]->callback();}
	static void isr34() {c_array[34]->callback();}
	static void isr35() {c_array[35]->callback();}
	static void isr36() {c_array[36]->callback();}
	static void isr37() {c_array[37]->callback();}
	static void isr38() {c_array[38]->callback();}
	static void isr39() {c_array[39]->callback();}
	static void isr40() {c_array[40]->callback();}
    static void isr41() {c_array[41]->callback();}
	static void isr42() {c_array[42]->callback();}
	static void isr43() {c_array[43]->callback();}
	static void isr44() {c_array[44]->callback();}
	static void isr45() {c_array[45]->callback();}
	static void isr46() {c_array[46]->callback();}
	static void isr47() {c_array[47]->callback();}
	static void isr48() {c_array[48]->callback();}
	static void isr49() {c_array[49]->callback();}
	static void isr50() {c_array[50]->callback();}
	static void isr51() {c_array[51]->callback();}
	static void isr52() {c_array[52]->callback();}
	static void isr53() {c_array[53]->callback();}
	static void isr54() {c_array[54]->callback();}
	static void isr55() {c_array[55]->callback();}
	static void isr56() {c_array[56]->callback();}
	static void isr57() {c_array[57]->callback();}
	static void isr58() {c_array[58]->callback();}
	static void isr59() {c_array[59]->callback();}
	static void isr60() {c_array[60]->callback();}
    static void isr61() {c_array[61]->callback();}
	static void isr62() {c_array[62]->callback();}
	static void isr63() {c_array[63]->callback();}

	static constexpr void(*isr_ptr[INTERRUPT_SIZE])(void) = { isr0, isr1, isr2,  isr3,  isr4, 
                                                            isr5,  isr6,  isr7,  isr8,  isr9, 
                                                            isr10, isr11, isr12, isr13, isr14, 
                                                            isr15, isr16, isr17, isr18, isr19, 
                                                            isr20, isr21, isr22, isr23, isr24,
                                                            isr25, isr26, isr27, isr28, isr29, 
                                                            isr30, isr31, isr32, isr33, isr34,
                                                            isr35, isr36, isr37, isr38, isr39, 
                                                            isr40, isr41, isr42, isr43, isr44,
                                                            isr45, isr46, isr47, isr48, isr49, 
                                                            isr50, isr51, isr52, isr53, isr54,
                                                            isr55, isr56, isr57, isr58, isr59, 
                                                            isr60, isr61, isr62, isr63 };
    
    func_ptr get_func_ptr(uint8_t pin)
    {
        return isr_ptr[pin];
    }

    void attach(uint8_t pin, Callable* callable)
    {
        detach(pin);
        c_array[pin] = callable;
    }

	void detach(uint8_t pin)
	{
		if (c_array[pin] != nullptr)
		{
			delete c_array[pin];
		}
	}
}