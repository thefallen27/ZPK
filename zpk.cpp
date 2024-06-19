#include <concepts>
#include <iostream>
#include <random>

template<typename T>
concept MPInt = std::integral<T> || std::same_as<T, long long>;

static void
generate_parameters(MPInt auto& p, MPInt auto& g)
{
    p = 23; // Example prime
    g = 5;  // Example generator
}

static void
prover_commitment(const MPInt auto& p, const MPInt auto& g, 
                  MPInt auto& r, MPInt auto& t)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<long long> dis(0, p - 2); // [0, p-1)
    r = dis(gen);
    t = 1;
    
    for (MPInt auto i = 0; i < r; ++i)
    {
        t = (t * g) % p;
    }
}

static void
prover_response(const MPInt auto& p, const MPInt auto& r, const MPInt auto& x,
                const MPInt auto& c, MPInt auto& s)
{
    s = (r + c * x) % (p - 1);
}

static bool
verifier_check(const MPInt auto& p, const MPInt auto& g, const MPInt auto& y,
               const MPInt auto& t, const MPInt auto& c, const MPInt auto& s)
{
    long long lhs = 1, rhs = t, yc = 1;

    for (MPInt auto i = 0; i < s; ++i)
    {
        lhs = (lhs * g) % p;
    }

    for (MPInt auto i = 0; i < c; ++i)
    {
        yc = (yc * y) % p;
    }

    rhs = (rhs * yc) % p;

    return lhs == rhs;
}

int main()
{
    long long p, g, x, y, r, t, c, s;

    generate_parameters(p, g);

    x = 6; // The secret
    y = 1;
    for (long long i = 0; i < x; ++i)
    {
        y = (y * g) % p;
    }

    prover_commitment(p, g, r, t);
    
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<long long> dis(0, p - 2);
    c = dis(gen);

    prover_response(p, r, x, c, s);

    if (verifier_check(p, g, y, t, c, s))
    {
        std::cout << "Proof is valid." << std::endl;
    }
    else
    {
        std::cout << "Proof is invalid." << std::endl;
    }

    return 0;
}
