# Lab Report: Secret Key Encryption Lab

Robert D. Hernandez <rherna70@uic.edu>

## Env Setup

Disable Address Space Layout Randomization

`sudo sysctl -w kernel.randomize_va_space=0`

## Task 1: Frequency Analysis

Given some trial and error first substituted the longest n-grams with the highest ngrams "the" and "and", then moved onto a few longer 2-n grams testing "in" and "er" and from there I was able to make out some smaller words and was able to character-by-character read and translate the doc.  The resulting key was "ytnvupmuqxifahlbrcdzgsokejw" and the plantext is viewable with:

```sh
tr 'ytnvupmuqxifahlbrcdzgsokejw' 'THEANDINSOLVCRWFGMYUBKJXPQZ' < ciphertext.txt > out.txt
```

## Task 2:

Below you can see the encryption commands I used, I tried all three cipher modes described, it seems like my vm did not support `-bf-cbc`

```sh
openssl enc -aes-128-cbc -e -in plain.txt -out cipher.bin \
    -K 00112233445566778889aabbccddeeff \
    -iv 0102030405060708

openssl enc -bf-cbc -e -in plain.txt -out cipher.bin \
    -K 00112233445566778889aabbccddeeff \
    -iv 0102030405060708

openssl enc -aes-128-cfb -e -in plain.txt -out cipher.bin \
    -K 00112233445566778889aabbccddeeff \
    -iv 0102030405060708
```

![alt text](images/task2.png)

## Task 3:
## Task 4:
## Task 5:
## Task 6:
## Task 7:
