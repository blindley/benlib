#include <stdexcept>

class Quantity
{
public:
    struct IncompatibleTypes : public std::runtime_error {        
        IncompatibleTypes() :std::runtime_error("") {}
    };
    
    constexpr Quantity() {}
    constexpr Quantity(double v) :value_(v) {}
    constexpr Quantity(double v, int m, int s, int g)
        :value_(v), meters_(m), seconds_(s), grams_(g)
    {}
    
    Quantity & operator *=(const Quantity & rhs)
    {
        value_ *= rhs.value_;
        meters_ += rhs.meters_;
        seconds_ += rhs.seconds_;
        grams_ += rhs.grams_;
        return *this;
    }
    
    Quantity & operator /=(const Quantity & rhs)
    {
        value_ /= rhs.value_;
        meters_ -= rhs.meters_;
        seconds_ -= rhs.seconds_;
        grams_ -= rhs.grams_;
        return *this;
    }
    
    Quantity & operator +=(const Quantity & rhs)
    {
        if (meters_ != rhs.meters_
         || seconds_ != rhs.seconds_
         || grams_ != rhs.grams_)
        {
            throw IncompatibleTypes();
        }
        
        value_ += rhs.value_;
        return *this;
    }
    
    Quantity & operator -=(const Quantity & rhs)
    {
        if (meters_ != rhs.meters_
         || seconds_ != rhs.seconds_
         || grams_ != rhs.grams_)
        {
            throw IncompatibleTypes();
        }
        
        value_ -= rhs.value_;
        return *this;
    }
    
    std::string to_string() const
    {
        auto val = [&]() { return std::to_string(value_); };
        auto kval = [&]() { return std::to_string(value_ / 1000); };
        auto verbose = [&]() { return val() + " " + verbose_units(); };
            
        if (meters_ == 0) {
            if (seconds_ == -1) {
                if (grams_ == 0) {
                    return val() + " hertz";
                }
            } else if (seconds_ == 0) {
                if (grams_ == 0) {
                    return val();
                } else if (grams_ == 1) {
                    return kval() + " Kg";
                }
            }
        } else if (meters_ == 1) {
            if (seconds_ == -2) {
                if (grams_ == 1) {
                    return kval() + " N";
                }
            }
        } else if (meters_ == 2) {
            if (seconds_ == -2) {
                if (grams_ == 1) {
                    return kval() + " J";
                }
            }
        }
        
        return verbose();
    }
    
    static constexpr Quantity meters(double v)
    { return Quantity(v,1,0,0); }    
    static constexpr Quantity seconds(double v)
    { return Quantity(v,0,1,0); }    
    static constexpr Quantity grams(double v)
    { return Quantity(v,0,0,1); }
    
    static constexpr Quantity kilometers(double v)
    { return Quantity(v*1000,1,0,0); }
    static constexpr Quantity kilograms(double v)
    { return Quantity(v*1000,0,0,1); }
    
    static constexpr Quantity newtons(double v)
    { return Quantity(v*1000,1,-2,1); }
    static constexpr Quantity joules(double v)
    { return Quantity(v*1000,2,-2,1); }
    
private:
    double value_ = 0.0;
    int meters_ = 0;
    int seconds_ = 0;
    int grams_ = 0;
    
    std::string verbose_units() const
    {
        std::string ret;
        if (meters_) {
            ret += 'm';
            if (meters_ != 1) {
                ret += '^';
                ret += std::to_string(meters_);
            }
        }
        if (grams_) {
            ret += 'g';
            if (grams_ != 1) {
                ret += '^';
                ret += std::to_string(grams_);
            }
        }
        if (seconds_) {
            ret += 's';
            if (seconds_ != 1) {
                ret += '^';
                ret += std::to_string(seconds_);
            }
        }
        
        return ret;        
    }
};

Quantity operator+(Quantity lhs, const Quantity & rhs)
    { return lhs += rhs; }
Quantity operator-(Quantity lhs, const Quantity & rhs)
    { return lhs -= rhs; }
Quantity operator*(Quantity lhs, const Quantity & rhs)
    { return lhs *= rhs; }
Quantity operator/(Quantity lhs, const Quantity & rhs)
    { return lhs /= rhs; }

std::ostream & operator<<(std::ostream & os, const Quantity & q)
{
    return os << q.to_string();
}
