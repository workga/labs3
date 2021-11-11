#include "pch.h"
#include "framework.h"

#include "element.h"
#include "class.h"


    Stack::Stack(Element *elements, int size)
    {
      SZ = QUOTA;
      if(size <= SZ)
      {
        top = size;
        stack = new Element[SZ];

        for(int i = 0; i < top; i++)
          stack[i] = elements[i];
      }
      else
      {
        while(size > SZ)
          SZ += QUOTA;

        top = size;
        stack = new Element[SZ];

        for(int i = 0; i < top; i++)
          stack[i] = elements[i];
      }
    }

    Stack::Stack(const Stack &st) : SZ(st.SZ), top(st.top)
    {
      stack = new Element[SZ];
      for(int i = 0; i < top; i++)
        stack[i] = st.stack[i];
    }

    Stack::Stack(Stack &&st) : SZ(st.SZ), top(st.top), stack(st.stack)
    {
      st.stack = nullptr;
    }

    int Stack::pop(Element &el)
    {
      if(top > 0)
        el = stack[--top];
      else
        throw std::runtime_error("Stack is empty!");
      return top;
    }

    int Stack::push(const Element &el)
    {
      if(top >= SZ){
        SZ += QUOTA;
        Element *old = stack;
        stack = new Element[SZ];

        for(int i = 0; i < top; ++i)
          stack[i] = old[i];

        delete[] old;
      }
      stack[top++] = el;
      return top;
    }

    bool Stack::isEmpty () const
    {
      if(!top)
        return true;
      return false;
    }

    bool Stack::isFilled () const
    {
      if(top && top < SZ)
        return true;
      return false;
    }

    Stack & Stack::operator =(const Stack &st)
    {
      if(this != &st)
      {
        top = st.top;
        SZ = st.SZ;
        delete[] stack;
        stack = new Element[SZ];

        for (int i = 0; i < top; ++i)
          stack[i] = st.stack[i];
      }
      return *this;
    }

    Stack & Stack::operator =(Stack &&st)
    {
      int tmp = top;
      top = st.top;
      st.top = tmp;
      tmp = SZ;
      SZ = st.SZ;
      st.SZ = tmp;
      Element *ptr = stack;
      stack = st.stack;
      st.stack = ptr;
      return *this;
    }

    Stack & Stack::operator --()
    {
      if(top)
        top--;
      else
        throw std::runtime_error("Stack is empty!");
      return *this;
    }

    const Stack Stack::operator --(int a)
    {
      Stack x(*this);
      if(top)
        top--;
      else
        throw std::runtime_error("Stack is empty!");
      return x;
    }

    Stack & Stack::operator +=(Element el)
    {
      if(top >= SZ){
        SZ += QUOTA;
        Element *old = stack;
        stack = new Element[SZ];

        for(int i = 0; i < top; ++i)
          stack[i] = old[i];

        delete[] old;
      }
      stack[top++] = el;
      return *this;
    }

    std::ostream & operator <<(std::ostream &c, const Stack &st)
    {
      if(st.top == 0)
        c << "Stack is empty!\n";
      else
        for(int i = st.top - 1; i >= 0; i--)
          c << (i + 1) << "# : " << st.stack[i] << std::endl;

      return c;
    }

    std::istream & operator >>(std::istream &s, Stack &st)
    {
      Element el;

      s >> el;
      if(s.good())
        st.push(el);
      else
        s.setstate(std::ios::failbit);

      return s;
    }
