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

int compare_strings(const char *str1, const char *str2) {
    // Compare character by character
    while (*str1 != '\0' && *str2 != '\0') {
        if (*str1 != *str2) {
            return 0; // Strings are different
        }
        str1++;
        str2++;
    }

    // If we reach the end of both strings, they are the same if both are null-terminated
    return (*str1 == '\0' && *str2 == '\0');
}

int main ()
{
  BN_CTX *ctx = BN_CTX_new();

  BIGNUM *res = BN_new();

  BIGNUM *n = BN_new();
  BIGNUM *e = BN_new();
  BIGNUM *d = BN_new();
  BIGNUM *m = BN_new();
  BIGNUM *S = BN_new();

  // Let (e, n) be the b=public key
  // e's (hex value equals to decimal 65537)
  BN_hex2bn(&e, "010001");
  BN_hex2bn(&n, "AE1CD4DC432798D933779FBD46C6E1247F0CF1233595113AA51B450F18116115");

  // Initialize private key d which are given
  BN_hex2bn(&d, "74D806F9F3A62BAE331FFE3F0A68AFE35B3D2E4794148AACBC26AA381CD7D30D");

  // Initialize signature S d which are given
  BN_hex2bn(&S, "643D6F34902D9C7EC90CB0B2BCA36C47FA37165C0005CAB026C0542CBDB6802F");

  const char *M = "Launch a missile."; 
  
  // Verify the signature with
  // m = S^e mod n
  BN_mod_exp(res, S, e, n, ctx);
  m = res;
  printBN("Hex value of m=", m);

  // Convert the BIGNUM back into a binary string
  size_t bn_len = BN_num_bytes(m);  // Get the length of the binary representation
  unsigned char *output_bin = (unsigned char *)malloc(bn_len);

  if (output_bin == NULL) {
      fprintf(stderr, "Memory allocation failed\n");
      BN_free(m);
      return 1;
  }

  // Convert the BIGNUM back to a binary form
  BN_bn2bin(m, output_bin);

  // Convert the binary representation back to a string
  printf("String representation of m derived from S: ");
  for (size_t i = 0; i < bn_len; i++) {
      printf("%c", output_bin[i]);
  }
  printf("\n");

  if (compare_strings(M, output_bin)) {
      printf("string1 and string2 are the same.\n");
  } else {
      printf("string1 and string2 are different.\n");
  }

    // Clean up memory
  free(output_bin);
  BN_free(m);

  return 0;
}

