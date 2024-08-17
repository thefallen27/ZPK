#include <concepts>
#include <iostream>
#include <random>

template<typename T>
concept MPInt = std::integral<T>;

static void
generate_parameters(MPInt auto& prime, MPInt auto& generator)
{
    prime = 23;
    generator = 5;
}

static void
prover_commitment(const MPInt auto& prime, const MPInt auto& generator,
    MPInt auto& random_value, MPInt auto& commitment)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<long long> dis(0, prime - 2);
    random_value = dis(gen);
    commitment = 1;

    for (MPInt auto i = 0; i < random_value; ++i)
    {
        commitment = (commitment * generator) % prime;
    }
}

static void
prover_response(const MPInt auto& prime, const MPInt auto& random_value, const MPInt auto& private_key,
    const MPInt auto& challenge, MPInt auto& response)
{
    response = (random_value + challenge * private_key) % (prime - 1);
}

static bool
verifier_check(const MPInt auto& prime, const MPInt auto& generator, const MPInt auto& public_key,
    const MPInt auto& commitment, const MPInt auto& challenge, const MPInt auto& response)
{
    long long left_hand_side = 1, right_hand_side = commitment, public_key_modulo = 1;

    for (MPInt auto i = 0; i < response; ++i)
    {
        left_hand_side = (left_hand_side * generator) % prime;
    }

    for (MPInt auto i = 0; i < challenge; ++i)
    {
        public_key_modulo = (public_key_modulo * public_key) % prime;
    }

    right_hand_side = (right_hand_side * public_key_modulo) % prime;

    return left_hand_side == right_hand_side;
}

int main()
{
    long long prime, generator, private_key, public_key, random_value, commitment, challenge, response;

    generate_parameters(prime, generator);

    std::cout << "Please provide the private key: ";
    std::cin >> private_key;
    std::cout << "Please provide the public key: ";
    std::cin >> public_key;

    for (long long i = 0; i < private_key; ++i)
    {
        public_key = (public_key * generator) % prime;
    }

    prover_commitment(prime, generator, random_value, commitment);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<long long> dis(0, prime - 2);
    challenge = dis(gen);

    prover_response(prime, random_value, private_key, challenge, response);

    if (verifier_check(prime, generator, public_key, commitment, challenge, response))
    {
        std::cout << "Proof is valid." << std::endl;
    }
    else
    {
        std::cout << "Proof is invalid." << std::endl;
    }

    return 0;
}
