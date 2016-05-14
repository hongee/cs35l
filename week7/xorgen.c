int main() {

  for (int i = 0; i < 256; i++) {
    //printf("%d = %c\n", i ,i);
    printf("\\%.3o", (i ^ 42));
  }

}
