function hammingWeight(x){
x = x - ((x >> 1) & 0x55555555);
x = (x & 0x33333333) + ((x >> 2) & 0x33333333);
return ((x + (x >> 4) & 0xF0F0F0F) * 0x1010101) >> 24;
}