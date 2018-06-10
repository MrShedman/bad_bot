#pragma once

#include "Arduino.h"

namespace IRQ
{
    typedef void (*func_ptr)();

	template<typename ObjT>
	static void attach(uint8_t pin, void(ObjT::*cb)(), ObjT* obj, int mode);

	static void attach(uint8_t pin, void(*cb)(), int mode);

    class Callable
	{
	public:

		virtual ~Callable() 
        {
            ::detachInterrupt(pin);
        }

        virtual void callback() = 0;

    protected:

        Callable(uint8_t pin, func_ptr fptr, int mode)
        :
        pin(pin)
        {
            ::attachInterrupt(pin, fptr, mode);
        }

        const uint8_t pin;
	};

	class CallableFunction: public Callable
	{
	public:
		
		typedef void(*CallbackT)();

		template<typename ObjT>
		friend void attach(uint8_t pin, void(ObjT::*cb)(), ObjT* obj, int mode);

		friend void attach(uint8_t pin, void(*cb)(), int mode);

		void callback() override
		{
			this->cb_();
		}

	private:

		CallableFunction(uint8_t pin, func_ptr fptr, CallbackT cb, int mode)
		:
        Callable(pin, fptr, mode),
		cb_(cb)
		{
		};

		CallbackT cb_;
	};

	template<typename ObjT>
	class CallableObject: public Callable
	{
	public:
		typedef void(ObjT::*CallbackT)();

		template<typename Obj>
		friend void attach(uint8_t pin, void(Obj::*cb)(), Obj* obj, int mode);

		friend void attach(uint8_t pin, void(*cb)(), int mode);

		void callback() override
		{
			(obj_->*cb_)();
		}

	private:

		CallableObject(uint8_t pin, func_ptr fptr, CallbackT cb, ObjT* obj, int mode)
		:
        Callable(pin, fptr, mode),
		cb_(cb),
		obj_(obj)
		{
		};

		CallbackT cb_;
		ObjT* obj_;
	};

	void detach(uint8_t pin);
    void attach(uint8_t pin, Callable* callable);

    func_ptr get_func_ptr(uint8_t pin);

	template<typename ObjT>
	static void attach(uint8_t pin, void(ObjT::*cb)(), ObjT* obj, int mode)
	{
        if (digitalPinToInterrupt(pin) != -1)
        {
		    attach(pin, new CallableObject<ObjT>{pin, get_func_ptr(pin), cb, obj, mode});
	    }
    }

	static void attach(uint8_t pin, void(*cb)(), int mode)
	{      
        if (digitalPinToInterrupt(pin) != -1)
        {
		    attach(pin, new CallableFunction {pin, get_func_ptr(pin), cb, mode});
        }
	}
}