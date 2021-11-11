#include "pch.h"
#include "framework.h"

#include "element.h"

    std::ostream & Element::print(std::ostream &s) const
    {
        s << "( " << _a << ", " << _b << " )";
        return s;
    }

    std::istream & Element::scan(std::istream &s)
    {
        s >> _a >> _b;
        if(!s.good())
            s.setstate(std::ios::failbit);

        return s;
    }

    std::ostream & operator<< (std::ostream &c, const Element & el)
    {
        return el.print(c);
    }

    std::istream & operator>> (std::istream &s, Element & el)
    {
        return el.scan(s);
    }
