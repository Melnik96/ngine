int main() {
  char* a = 0;
  char* b = a + sizeof(int);
  printf("b = 0x%x\n", b);
}
