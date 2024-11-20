#include <stdio.h>
#include <openssl/bn.h>

#define NBITS 256

void printBN(char *msg, BIGNUM * a)
{
   /* Use BN_bn2hex(a) for hex string
    * Use BN_bn2dec(a) for decimal string */
   char * number_str = BN_bn2hex(a);
   printf("%s %s\n", msg, number_str);
   OPENSSL_free(number_str);
}

int main ()
{
  BN_CTX *ctx = BN_CTX_new();

  BIGNUM *res = BN_new();

  BIGNUM *p = BN_new();
  BIGNUM *q = BN_new();
  BIGNUM *n = BN_new();

  // BN_generate_prime_ex(a, NBITS, 1, NULL, NULL, NULL);
  // BN_dec2bn(&b, "273489463796838501848592769467194369268");

  // Initialize p, q, n
  BN_hex2bn(&p, "F7E75FDC469067FFDC4E847C51F452DF");
  BN_hex2bn(&q, "E85CED54AF57E53E092113E62F436F4F");
  BN_rand(n, NBITS, 0, 0);

  // Assign a value from a hex number string
  BN_mul(n, p, q, ctx);
  printBN("n=", n);

  return 0;
}

