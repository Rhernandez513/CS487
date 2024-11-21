#include <stdio.h>
#include <string.h>
#include <openssl/sha.h>
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

  BIGNUM *n = BN_new();
  BIGNUM *e = BN_new();
  BIGNUM *d = BN_new();
  BIGNUM *m = BN_new();
  BIGNUM *s = BN_new();

  // Let (e, n) be the b=public key
  // e's (hex value equals to decimal 65537)
  BN_hex2bn(&e, "010001");
  BN_hex2bn(&n, "DCBFFE3E51F62E09CE7032E2677A78946A849DC4CDDE3A4D0CB81629242FB1A5");

  // Initialize private key d which are given
  BN_hex2bn(&d, "74D806F9F3A62BAE331FFE3F0A68AFE35B3D2E4794148AACBC26AA381CD7D30D");

  // The input string
  // Task 4.1
  // const char *M = "M = I owe you $2000";
  // Task 4.2
  const char *M = "M = I owe you $3000"; 
  
  // Convert the string to a binary representation
  size_t str_len = strlen(M);
  unsigned char *bin = (unsigned char *)malloc(str_len);

  if (bin == NULL) {
      fprintf(stderr, "Memory allocation failed\n");
      return 1;
  }

  // Copy the string into the binary buffer
  memcpy(bin, M, str_len);

  // Store the string as a BigNumber
  if (BN_bin2bn(bin, str_len, m) == NULL) {
      fprintf(stderr, "BN_bin2bn failed\n");
      free(bin);
      BN_free(m);
      return 1;
  }

  // Sign the message
  // Digital Signature = m^d mod n
  BN_mod_exp(res, m, d, n, ctx);
  s = res;
  printBN("Hex value of digital signature =", s);

  // Convert the BIGNUM back into a binary string
  size_t bn_len = BN_num_bytes(s);  // Get the length of the binary representation
  unsigned char *output_bin = (unsigned char *)malloc(bn_len);

  if (output_bin == NULL) {
      fprintf(stderr, "Memory allocation failed\n");
      free(bin);
      BN_free(s);
      return 1;
  }

  // Convert the BIGNUM back to a binary form
  BN_bn2bin(s, output_bin);

  // Convert the binary representation back to a string
  printf("String representation of Digital Signature: ");
  for (size_t i = 0; i < bn_len; i++) {
      printf("%c", output_bin[i]);
  }
  printf("\n");

    // Clean up memory
  free(bin);
  free(output_bin);
  BN_free(s);

  return 0;
}

