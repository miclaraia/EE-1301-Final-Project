
8x8-bicolor.ino  


96
97
98
99
100
101
102
103
104
105
106
107
108
109
110
111
112
113
114
115
116
117
118
119
120
121
122
123
124
125
126
127
128
129
130
131
132
133
134
135
136
137
138
139
140
141
142
143
    B11100001 },
 botright_bmp[] =
  { B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00011110,
    B00011110,
    B00011110,
    B00011110 },
 X_bmp[] =
  { B00000011,
    B10000100,
    B01001000,
    B00110000,
    B00110000,
    B01001000,
    B10000100,
    B00000011 },
 clean_bmp[] =
  { B11111111,
    B11111111,
    B11111111,
    B11111111,
    B11111111,
    B11111111,
    B11111111,
    B11111111 };
    
void simon(){
    
    int number = 0;
    int disp[R+1];
    int check[R];
    for(int i =0; i<R; i++){
        check[i]=0;
    }
    int TL_ButNow;
    int TR_ButNow;
    int BL_ButNow;
    int BR_ButNow;
    int SZ_ButNow;
    int TL_ButLast = 0;
    int TR_ButLast = 0;
    int BL_ButLast = 0;
    int BR_ButLast = 0;
    int SZ_ButLast = 0;
    
Firmware was saved successfully.