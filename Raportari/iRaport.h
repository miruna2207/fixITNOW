#include "../ServiceManager.h"

class iRaport{
    public:
    virtual ~iRaport() = default;
    virtual void top_angajati_salariu() const = 0;
    virtual void longest_reparatie() const = 0;
    virtual void ordoneaza_cereri() = 0;
};