module main(input[31:0] in1, in2, in3);

  // follows
  // http://www.asic-world.com/verilog/operators1.html

  // arithmetic
  always assert arith_p1: 5  +  10 ==  15;
  always assert arith_p2: 5  -  10 ==  -5;
  always assert arith_p3: 10 -   5 ==   5;
  always assert arith_p4: 10 *   5 ==  50;
  always assert arith_p5: 10 /   5 ==   2;
  always assert arith_p6: 10 /  -5 ==  -2;
  always assert arith_p7: 10 %   3 ==   1;
  always assert arith_p8: +5       ==   5;
  always assert arith_p9: -5       ==  -5;

  // relational
  always assert rel_p1: (5    <= 10) == 1;
  always assert rel_p2: (5    >= 10) == 0;
  always assert rel_p3: (1'bx <= 10) == 1'bx;
  always assert rel_p4: (1'bz <= 10) == 1'bx;
  always assert rel_p5: (-10  <= 10) == 1;

  // equality
  always assert equal_p1:  (4'bx001 ===  4'bx001) == 1;
  always assert equal_p2:  (4'bx0x1 ===  4'bx001) == 0;
  always assert equal_p3:  (4'bz0x1 ===  4'bz0x1) == 1;
  always assert equal_p4:  (4'bz0x1 ===  4'bz001) == 0;
  always assert equal_p5:  (4'bx0x1 !==  4'bx001) == 1;
  always assert equal_p6:  (4'bz0x1 !==  4'bz001) == 1;
  always assert equal_p7:  (5       ==   10     ) == 0;
  always assert equal_p8:  (5       ==    5     ) == 1;
  always assert equal_p9:  (5       !=    5     ) == 0;
  always assert equal_p10: (5       !=    6     ) == 1;    

  // logical
  always assert logic_p1: (1'b1 && 1'b1) == 1;
  always assert logic_p2: (1'b1 && 1'b0) == 0;
//  always assert logic_p3: (1'b1 && 1'bx) == x;
  always assert logic_p4: (1'b1 || 1'b0) == 1;
  always assert logic_p5: (1'b0 || 1'b0) == 0;
//  always assert logic_p6: (1'b0 || 1'bx) == x;
  always assert logic_p7: (! 1'b1      ) == 0;
  always assert logic_p8: (! 1'b0      ) == 1;

  // bit-wise
  always assert bit_p1:  ~4'b0001           == 'b1110;
  always assert bit_p2:  ~4'bx001           == 'bx110;
  always assert bit_p3:  ~4'bz001           == 'bx110;
  always assert bit_p4:  4'b0001 &  4'b1001 == 'b0001;
  always assert bit_p5:  4'b1001 &  4'bx001 == 'bx001;
  always assert bit_p6:  4'b1001 &  4'bz001 == 'bx001;
  always assert bit_p7:  4'b0001 |  4'b1001 == 'b1001;
  always assert bit_p8:  4'b0001 |  4'bx001 == 'bx001;
  always assert bit_p9:  4'b0001 |  4'bz001 == 'bx001;
  always assert bit_p10: 4'b0001 ^  4'b1001 == 'b1000;
  always assert bit_p11: 4'b0001 ^  4'bx001 == 'bx000;
  always assert bit_p12: 4'b0001 ^  4'bz001 == 'bx000;
  always assert bit_p13: 4'b0001 ~^ 4'b1001 == 'b0111;
  always assert bit_p14: 4'b0001 ~^ 4'bx001 == 'bx111;
  always assert bit_p15: 4'b0001 ~^ 4'bz001 == 'bx111;                 

  // reduction
  always assert redu_p1:   & 4'b1001 == 0;
  always assert redu_p2:   & 4'bx111 == x;
  always assert redu_p3:   & 4'bz111 == x;
  always assert redu_p4:  ~& 4'b1001 == 1;
  always assert redu_p5:  ~& 4'bx001 == 1;
  always assert redu_p6:  ~& 4'bz001 == 1;
  always assert redu_p7:   | 4'b1001 == 1;
  always assert redu_p8:   | 4'bx000 == x;
  always assert redu_p9:   | 4'bz000 == x;
  always assert redu_p10: ~| 4'b1001 == 0;
  always assert redu_p11: ~| 4'bx001 == 0;
  always assert redu_p12: ~| 4'bz001 == 0;
  always assert redu_p13:  ^ 4'b1001 == 0;
  always assert redu_p14:  ^ 4'bx001 == x;
  always assert redu_p15:  ^ 4'bz001 == x;
  always assert redu_p16: ~^ 4'b1001 == 1;
  always assert redu_p17: ~^ 4'bx001 == x;
  always assert redu_p18: ~^ 4'bz001 == x;

  // shift
  always assert shift_p1: 4'b1001 << 1 == 'b0010;
  always assert shift_p2: 4'b10x1 << 1 == 'b0x10;
  always assert shift_p3: 4'b10z1 << 1 == 'b0z10;
  always assert shift_p4: 4'b1001 >> 1 == 'b0100;
  always assert shift_p5: 4'b10x1 >> 1 == 'b010x;
  always assert shift_p6: 4'b10z1 >> 1 == 'b010z;

  // concatenation
  always assert concat_p1: {4'b1001,4'b10x1} == 'b100110x1;

  // replication
  always assert repli_p1: {4{4'b1001}}      == 'b1001100110011001;
  always assert repli_p2: {4{4'b1001,1'bz}} == 'b1001z1001z1001z1001z;

endmodule