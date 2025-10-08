#ifndef BASE_HPP
#define BASE_HPP

class Base {
    private:
        Base();
        Base * generate(void);
        void identify(Base* p);
        void identify(Base& p);
    public :
        virtual ~Base();
};

#endif