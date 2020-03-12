xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 237;
 0.27777;1.41811;-0.39411;,
 -2.14425;0.56475;-4.27943;,
 -2.92559;-0.34055;-1.87915;,
 0.27777;1.41811;-0.39411;,
 -2.92559;-0.34055;-1.87915;,
 -2.02367;-0.35017;2.13559;,
 0.27777;1.41811;-0.39411;,
 -2.02367;-0.35017;2.13559;,
 1.09882;-1.11569;3.99473;,
 1.01240;-0.04637;-4.90954;,
 0.27777;1.41811;-0.39411;,
 2.80572;0.12521;-2.21522;,
 0.27777;1.41811;-0.39411;,
 3.50391;-0.36275;0.49527;,
 2.80572;0.12521;-2.21522;,
 0.27777;1.41811;-0.39411;,
 3.00010;-0.34516;2.63396;,
 3.50391;-0.36275;0.49527;,
 0.27777;1.41811;-0.39411;,
 1.09882;-1.11569;3.99473;,
 3.00010;-0.34516;2.63396;,
 -2.02367;-0.35017;2.13559;,
 -2.92559;-0.34055;-1.87915;,
 -3.18385;-2.61021;-0.19941;,
 -2.02367;-0.35017;2.13559;,
 -3.18385;-2.61021;-0.19941;,
 -2.42250;-3.78930;2.44786;,
 1.09882;-1.11569;3.99473;,
 -2.02367;-0.35017;2.13559;,
 -2.42250;-3.78930;2.44786;,
 0.16495;-3.90317;4.47902;,
 -2.14425;0.56475;-4.27943;,
 0.27777;1.41811;-0.39411;,
 1.01240;-0.04637;-4.90954;,
 1.01240;-0.04637;-4.90954;,
 2.80572;0.12521;-2.21522;,
 3.01488;-2.13456;-2.56423;,
 3.50391;-0.36275;0.49527;,
 3.60873;-3.69650;-0.06713;,
 3.01488;-2.13456;-2.56423;,
 2.80572;0.12521;-2.21522;,
 3.00010;-0.34516;2.63396;,
 3.16999;-4.35373;2.70646;,
 3.60873;-3.69650;-0.06713;,
 3.50391;-0.36275;0.49527;,
 1.09882;-1.11569;3.99473;,
 3.16999;-4.35373;2.70646;,
 3.00010;-0.34516;2.63396;,
 1.01240;-0.04637;-4.90954;,
 2.13163;-3.01167;-5.16155;,
 -0.88793;-1.24067;-7.20556;,
 2.13163;-3.01167;-5.16155;,
 1.01240;-0.04637;-4.90954;,
 3.01488;-2.13456;-2.56423;,
 -2.14425;0.56475;-4.27943;,
 1.01240;-0.04637;-4.90954;,
 -0.88793;-1.24067;-7.20556;,
 -5.57691;-6.54638;-13.49180;,
 -5.82838;-6.04424;-9.97180;,
 -4.44770;-4.74294;-12.85555;,
 -4.44770;-4.74294;-12.85555;,
 -2.81280;-5.92062;-14.57233;,
 -5.57691;-6.54638;-13.49180;,
 -1.95890;-3.98175;-12.09578;,
 -2.81280;-5.92062;-14.57233;,
 -0.37884;-6.43152;-12.98727;,
 -2.81280;-5.92062;-14.57233;,
 -1.95890;-3.98175;-12.09578;,
 -2.42250;-3.78930;2.44786;,
 -3.18385;-2.61021;-0.19941;,
 -2.87696;-6.32382;0.58386;,
 0.16495;-3.90317;4.47902;,
 -2.42250;-3.78930;2.44786;,
 -0.94404;-6.41211;3.78962;,
 3.01488;-2.13456;-2.56423;,
 2.84534;-5.09986;-2.84487;,
 2.13163;-3.01167;-5.16155;,
 2.84534;-5.09986;-2.84487;,
 3.60873;-3.69650;-0.06713;,
 -2.87696;-6.32382;0.58386;,
 -0.94404;-6.41211;3.78962;,
 -2.42250;-3.78930;2.44786;,
 -0.94404;-6.41211;3.78962;,
 1.78355;-6.72556;3.16352;,
 0.16495;-3.90317;4.47902;,
 2.12560;-6.85238;-0.54812;,
 3.60873;-3.69650;-0.06713;,
 3.16999;-4.35373;2.70646;,
 1.78355;-6.72556;3.16352;,
 1.78355;-6.72556;3.16352;,
 3.16999;-4.35373;2.70646;,
 0.16495;-3.90317;4.47902;,
 2.84534;-5.09986;-2.84487;,
 3.60873;-3.69650;-0.06713;,
 2.12560;-6.85238;-0.54812;,
 1.48866;-7.09016;-2.71141;,
 -4.25768;-3.55452;-9.90728;,
 -5.82838;-6.04424;-9.97180;,
 -5.51508;-6.16608;-7.48471;,
 2.16375;-6.25497;-5.23532;,
 1.96728;-4.17038;-7.48943;,
 2.13163;-3.01167;-5.16155;,
 3.16999;-4.35373;2.70646;,
 1.09882;-1.11569;3.99473;,
 0.16495;-3.90317;4.47902;,
 -5.57691;-6.54638;-13.49180;,
 -2.81280;-5.92062;-14.57233;,
 -3.63992;-7.30240;-12.70242;,
 -0.37884;-6.43152;-12.98727;,
 0.62074;-7.10111;-10.57161;,
 -3.15224;-7.26463;-10.39083;,
 -1.01403;-7.20202;-7.84447;,
 -1.01403;-7.20202;-7.84447;,
 0.62074;-7.10111;-10.57161;,
 1.37824;-7.01012;-8.13756;,
 2.12560;-6.85238;-0.54812;,
 -0.51017;-7.24009;0.72815;,
 -1.04233;-7.19216;-1.90982;,
 1.78355;-6.72556;3.16352;,
 -1.04233;-7.19216;-1.90982;,
 1.48866;-7.09016;-2.71141;,
 2.12560;-6.85238;-0.54812;,
 -1.42232;-7.17464;-4.88787;,
 1.48866;-7.09016;-2.71141;,
 -1.04233;-7.19216;-1.90982;,
 2.16375;-6.25497;-5.23532;,
 -1.42232;-7.17464;-4.88787;,
 -1.01403;-7.20202;-7.84447;,
 1.37824;-7.01012;-8.13756;,
 2.16375;-6.25497;-5.23532;,
 -0.51017;-7.24009;0.72815;,
 1.78355;-6.72556;3.16352;,
 -0.94404;-6.41211;3.78962;,
 -2.87696;-6.32382;0.58386;,
 -1.04233;-7.19216;-1.90982;,
 -2.87696;-6.32382;0.58386;,
 -1.04233;-7.19216;-1.90982;,
 -2.87696;-6.32382;0.58386;,
 -4.05948;-6.07675;-3.28899;,
 -1.42232;-7.17464;-4.88787;,
 -1.42232;-7.17464;-4.88787;,
 -4.05948;-6.07675;-3.28899;,
 -5.03107;-6.36166;-5.26710;,
 -5.57691;-6.54638;-13.49180;,
 -3.63992;-7.30240;-12.70242;,
 -3.15224;-7.26463;-10.39083;,
 -5.82838;-6.04424;-9.97180;,
 -0.37884;-6.43152;-12.98727;,
 -3.15224;-7.26463;-10.39083;,
 -3.63992;-7.30240;-12.70242;,
 -2.81280;-5.92062;-14.57233;,
 -5.51508;-6.16608;-7.48471;,
 -3.66868;-2.10450;-6.13032;,
 -4.25768;-3.55452;-9.90728;,
 -4.92125;-4.03711;-5.19899;,
 -2.32360;-2.31129;-9.18000;,
 -3.66868;-2.10450;-6.13032;,
 -0.88793;-1.24067;-7.20556;,
 -3.66868;-2.10450;-6.13032;,
 -2.32360;-2.31129;-9.18000;,
 -4.25768;-3.55452;-9.90728;,
 -0.88793;-1.24067;-7.20556;,
 0.20698;-2.99915;-9.73910;,
 -2.32360;-2.31129;-9.18000;,
 1.96728;-4.17038;-7.48943;,
 0.20698;-2.99915;-9.73910;,
 -0.88793;-1.24067;-7.20556;,
 1.96728;-4.17038;-7.48943;,
 1.36289;-4.91680;-10.47497;,
 0.20698;-2.99915;-9.73910;,
 -4.05948;-6.07675;-3.28899;,
 -2.87696;-6.32382;0.58386;,
 -3.94380;-3.60845;-2.66725;,
 2.16375;-6.25497;-5.23532;,
 2.84534;-5.09986;-2.84487;,
 1.48866;-7.09016;-2.71141;,
 -3.18385;-2.61021;-0.19941;,
 -3.94380;-3.60845;-2.66725;,
 -2.87696;-6.32382;0.58386;,
 -3.66868;-2.10450;-6.13032;,
 -2.92559;-0.34055;-1.87915;,
 -2.14425;0.56475;-4.27943;,
 -3.94380;-3.60845;-2.66725;,
 -2.14425;0.56475;-4.27943;,
 -0.88793;-1.24067;-7.20556;,
 -3.66868;-2.10450;-6.13032;,
 -4.25768;-3.55452;-9.90728;,
 -4.25768;-3.55452;-9.90728;,
 -4.44770;-4.74294;-12.85555;,
 -1.95890;-3.98175;-12.09578;,
 -2.32360;-2.31129;-9.18000;,
 -1.95890;-3.98175;-12.09578;,
 1.36289;-4.91680;-10.47497;,
 -0.37884;-6.43152;-12.98727;,
 0.20698;-2.99915;-9.73910;,
 -2.32360;-2.31129;-9.18000;,
 -3.15224;-7.26463;-10.39083;,
 -3.17677;-7.20896;-7.57400;,
 -5.51508;-6.16608;-7.48471;,
 -5.82838;-6.04424;-9.97180;,
 0.62074;-7.10111;-10.57161;,
 1.36289;-4.91680;-10.47497;,
 1.37824;-7.01012;-8.13756;,
 1.36289;-4.91680;-10.47497;,
 -0.37884;-6.43152;-12.98727;,
 -3.17677;-7.20896;-7.57400;,
 -1.42232;-7.17464;-4.88787;,
 -5.03107;-6.36166;-5.26710;,
 -1.01403;-7.20202;-7.84447;,
 -3.17677;-7.20896;-7.57400;,
 -5.03107;-6.36166;-5.26710;,
 -5.51508;-6.16608;-7.48471;,
 1.37824;-7.01012;-8.13756;,
 1.96728;-4.17038;-7.48943;,
 2.16375;-6.25497;-5.23532;,
 1.96728;-4.17038;-7.48943;,
 1.37824;-7.01012;-8.13756;,
 1.36289;-4.91680;-10.47497;,
 -5.51508;-6.16608;-7.48471;,
 -5.03107;-6.36166;-5.26710;,
 -4.92125;-4.03711;-5.19899;,
 -3.66868;-2.10450;-6.13032;,
 -4.92125;-4.03711;-5.19899;,
 -3.94380;-3.60845;-2.66725;,
 -3.18385;-2.61021;-0.19941;,
 -2.92559;-0.34055;-1.87915;,
 -3.94380;-3.60845;-2.66725;,
 1.96728;-4.17038;-7.48943;,
 -0.88793;-1.24067;-7.20556;,
 2.13163;-3.01167;-5.16155;,
 2.16375;-6.25497;-5.23532;,
 2.13163;-3.01167;-5.16155;,
 2.84534;-5.09986;-2.84487;,
 -4.92125;-4.03711;-5.19899;,
 -5.03107;-6.36166;-5.26710;,
 -4.05948;-6.07675;-3.28899;,
 -3.94380;-3.60845;-2.66725;;
 
 96;
 3;0,1,2;,
 3;3,4,5;,
 3;6,7,8;,
 3;9,10,11;,
 3;12,13,14;,
 3;15,16,17;,
 3;18,19,20;,
 3;21,22,23;,
 3;24,25,26;,
 3;27,28,29;,
 3;27,29,30;,
 3;31,32,33;,
 3;34,35,36;,
 3;37,38,39;,
 3;37,39,40;,
 3;41,42,43;,
 3;41,43,44;,
 3;45,46,47;,
 3;48,49,50;,
 3;51,52,53;,
 3;54,55,56;,
 3;57,58,59;,
 3;60,61,62;,
 3;60,63,64;,
 3;65,66,67;,
 3;68,69,70;,
 3;71,72,73;,
 3;74,75,76;,
 3;77,74,78;,
 3;79,80,81;,
 3;82,83,84;,
 3;85,86,87;,
 3;85,87,88;,
 3;89,90,91;,
 3;92,93,94;,
 3;95,92,94;,
 3;96,97,98;,
 3;99,100,101;,
 3;102,103,104;,
 3;105,106,107;,
 3;108,109,110;,
 3;109,111,110;,
 3;112,113,114;,
 3;115,116,117;,
 3;116,115,118;,
 3;119,120,121;,
 3;122,123,124;,
 3;123,122,125;,
 3;126,127,128;,
 3;126,128,129;,
 3;130,131,132;,
 3;130,133,134;,
 3;135,130,132;,
 3;136,137,138;,
 3;139,136,138;,
 3;140,141,142;,
 3;143,144,145;,
 3;143,145,146;,
 3;147,148,149;,
 3;150,147,149;,
 3;151,152,153;,
 3;152,151,154;,
 3;155,156,157;,
 3;158,159,160;,
 3;161,162,163;,
 3;164,165,166;,
 3;167,168,169;,
 3;170,171,172;,
 3;173,174,175;,
 3;176,177,178;,
 3;179,180,181;,
 3;180,179,182;,
 3;183,184,185;,
 3;58,186,59;,
 3;187,63,188;,
 3;189,187,190;,
 3;191,192,193;,
 3;192,191,194;,
 3;191,195,194;,
 3;196,197,198;,
 3;196,198,199;,
 3;197,110,111;,
 3;200,201,202;,
 3;203,200,204;,
 3;205,206,207;,
 3;206,205,208;,
 3;209,210,211;,
 3;212,213,214;,
 3;215,216,217;,
 3;218,219,220;,
 3;221,222,223;,
 3;224,225,226;,
 3;227,228,229;,
 3;230,231,232;,
 3;233,234,235;,
 3;236,233,235;;
 
 MeshMaterialList {
  7;
  96;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0;;
  Material {
   0.440920;0.449680;0.472310;1.000000;;
   23.000000;
   0.700000;0.700000;0.700000;;
   0.253680;0.258720;0.271740;;
  }
  Material {
   0.144000;0.144000;0.144000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.326400;0.332800;0.571200;1.000000;;
   31.000000;
   0.350000;0.350000;0.350000;;
   0.097920;0.099840;0.171360;;
  }
  Material {
   0.298000;0.245000;0.251000;1.000000;;
   46.000000;
   0.710000;0.710000;0.710000;;
   0.417200;0.343000;0.351400;;
  }
  Material {
   0.542400;0.545600;0.144000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.097600;0.097600;0.097600;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.000000;1.000000;0.898000;1.000000;;
   100.000000;
   1.000000;1.000000;1.000000;;
   0.000000;1.000000;0.898000;;
  }
 }
 MeshNormals {
  67;
  0.030513;0.991976;0.122689;,
  0.740464;0.606520;-0.289565;,
  0.244071;0.917273;0.314707;,
  -0.700648;0.527533;0.480417;,
  -0.318469;0.605153;0.729635;,
  0.937580;0.109598;-0.330050;,
  0.836455;0.546526;0.040643;,
  -0.755841;0.636709;-0.152662;,
  0.858182;0.181265;-0.480278;,
  -0.508064;0.737278;-0.445301;,
  -0.659654;0.581165;-0.476554;,
  -0.781134;0.072882;0.620096;,
  -0.857940;-0.409922;0.309681;,
  0.696209;0.317579;-0.643767;,
  -0.507889;-0.433905;0.744160;,
  0.339119;-0.230616;0.912039;,
  0.990732;-0.135621;-0.007517;,
  -0.642409;0.736526;-0.211754;,
  0.466245;0.753305;-0.463841;,
  -0.926968;0.373775;0.031978;,
  -0.838038;0.533683;0.113468;,
  -0.956987;0.123718;0.262432;,
  -0.007410;-0.955135;-0.296077;,
  -0.167321;-0.985840;-0.011107;,
  0.619650;-0.784872;0.003174;,
  0.433222;-0.898570;-0.069926;,
  0.043377;-0.999007;0.010182;,
  -0.100767;-0.989283;0.105666;,
  -0.147869;-0.988497;0.031765;,
  -0.030064;-0.998208;0.051733;,
  -0.189146;0.889382;-0.416201;,
  0.923555;0.298902;-0.240216;,
  0.973909;-0.177514;-0.141385;,
  0.021601;0.689800;-0.723678;,
  0.142410;-0.987320;0.070134;,
  0.441848;0.758193;-0.479494;,
  0.820488;-0.185076;0.540876;,
  -0.004577;-0.022229;0.999742;,
  -0.953696;0.179970;0.240986;,
  -0.369263;0.879038;-0.301557;,
  -0.948659;0.230598;0.216496;,
  0.165131;0.779783;-0.603879;,
  -0.837431;0.543666;-0.055997;,
  0.051286;-0.994319;-0.093275;,
  -0.295209;-0.944700;0.142810;,
  -0.211585;-0.976356;0.044287;,
  0.944407;-0.276213;-0.178330;,
  0.226899;0.823510;-0.519949;,
  0.894118;0.234943;-0.381256;,
  -0.324819;-0.938637;0.115989;,
  0.816816;0.161156;-0.553931;,
  0.979110;0.063377;-0.193201;,
  0.900967;0.026965;0.433050;,
  0.539057;0.009723;0.842213;,
  0.369672;-0.916938;0.150223;,
  -0.307718;-0.939972;-0.147519;,
  0.057732;-0.814937;-0.576667;,
  0.156712;-0.943706;-0.291307;,
  0.244619;-0.968810;-0.039616;,
  -0.052748;-0.965834;0.253736;,
  -0.363440;-0.929907;0.056422;,
  -0.407220;-0.911700;0.054545;,
  -0.930571;-0.015882;0.365768;,
  -0.409268;-0.912358;0.010115;,
  0.890290;-0.286840;-0.353704;,
  0.954115;-0.205524;-0.217770;,
  -0.943656;0.034938;0.329080;;
  96;
  3;0,39,20;,
  3;0,20,3;,
  3;0,3,4;,
  3;35,0,1;,
  3;0,6,1;,
  3;0,2,6;,
  3;0,4,2;,
  3;3,20,21;,
  3;3,21,11;,
  3;4,3,11;,
  3;4,11,37;,
  3;39,0,35;,
  3;50,1,5;,
  3;51,16,5;,
  3;6,5,1;,
  3;52,36,16;,
  3;52,16,6;,
  3;53,36,52;,
  3;35,48,47;,
  3;48,35,5;,
  3;39,35,47;,
  3;10,42,9;,
  3;9,33,10;,
  3;9,41,33;,
  3;13,33,41;,
  3;11,21,12;,
  3;37,11,14;,
  3;5,46,48;,
  3;46,5,16;,
  3;12,14,11;,
  3;14,15,37;,
  3;24,16,36;,
  3;24,36,54;,
  3;15,36,37;,
  3;46,16,24;,
  3;25,46,24;,
  3;17,42,19;,
  3;32,31,48;,
  3;36,53,37;,
  3;55,56,22;,
  3;57,43,23;,
  3;43,26,23;,
  3;26,43,34;,
  3;24,27,28;,
  3;27,24,54;,
  3;28,25,24;,
  3;29,25,28;,
  3;25,29,58;,
  3;29,26,34;,
  3;29,34,58;,
  3;27,54,59;,
  3;27,60,28;,
  3;12,27,14;,
  3;28,12,49;,
  3;29,28,49;,
  3;29,49,44;,
  3;55,22,23;,
  3;55,23,61;,
  3;57,23,22;,
  3;56,57,22;,
  3;19,7,17;,
  3;7,19,40;,
  3;30,7,47;,
  3;7,30,17;,
  3;47,18,30;,
  3;31,18,47;,
  3;31,8,18;,
  3;62,12,38;,
  3;32,46,25;,
  3;21,38,12;,
  3;7,20,39;,
  3;20,7,38;,
  3;39,47,7;,
  3;42,17,9;,
  3;17,41,9;,
  3;41,17,30;,
  3;41,8,13;,
  3;8,41,18;,
  3;41,30,18;,
  3;23,45,63;,
  3;23,63,61;,
  3;45,23,26;,
  3;64,8,65;,
  3;8,64,13;,
  3;45,29,44;,
  3;29,45,26;,
  3;45,44,63;,
  3;65,31,32;,
  3;31,65,8;,
  3;19,66,40;,
  3;7,40,38;,
  3;21,20,38;,
  3;31,47,48;,
  3;32,48,46;,
  3;40,66,62;,
  3;38,40,62;;
 }
 MeshTextureCoords {
  237;
  0.836800;0.722300;,
  0.843700;0.724900;,
  0.838100;0.719600;,
  0.823000;0.712300;,
  0.831700;0.714200;,
  0.824400;0.708800;,
  0.798600;0.699600;,
  0.800600;0.695700;,
  0.794400;0.693200;,
  0.861300;0.758600;,
  0.859400;0.765600;,
  0.862400;0.765900;,
  0.859800;0.793200;,
  0.863700;0.793700;,
  0.863900;0.783400;,
  0.858900;0.803100;,
  0.862000;0.811700;,
  0.862900;0.803600;,
  0.856500;0.817600;,
  0.859900;0.824500;,
  0.860900;0.818500;,
  0.827500;0.701100;,
  0.834300;0.707200;,
  0.836900;0.700200;,
  0.820000;0.695300;,
  0.830600;0.693400;,
  0.824100;0.687100;,
  0.799100;0.682900;,
  0.805500;0.686300;,
  0.810500;0.676900;,
  0.803800;0.672700;,
  0.852300;0.735400;,
  0.853300;0.741800;,
  0.855400;0.740800;,
  0.871600;0.757600;,
  0.868700;0.766300;,
  0.874900;0.766800;,
  0.872500;0.794500;,
  0.881300;0.795200;,
  0.879700;0.785100;,
  0.871800;0.784200;,
  0.872300;0.813000;,
  0.882700;0.814300;,
  0.882300;0.805300;,
  0.872600;0.804400;,
  0.871600;0.827100;,
  0.882900;0.822400;,
  0.871900;0.820500;,
  0.882100;0.745800;,
  0.890100;0.752600;,
  0.886000;0.743000;,
  0.890200;0.764600;,
  0.882400;0.758600;,
  0.887000;0.770000;,
  0.875200;0.730600;,
  0.878600;0.737800;,
  0.882300;0.735300;,
  0.927900;0.682300;,
  0.919700;0.684500;,
  0.922100;0.690900;,
  0.934000;0.692200;,
  0.941400;0.688600;,
  0.937600;0.684300;,
  0.927900;0.703200;,
  0.937300;0.697500;,
  0.943300;0.708500;,
  0.940500;0.703200;,
  0.931700;0.710100;,
  0.831600;0.675300;,
  0.838900;0.680900;,
  0.840600;0.677400;,
  0.811000;0.661200;,
  0.819100;0.662700;,
  0.812900;0.658400;,
  0.893900;0.781400;,
  0.897600;0.776400;,
  0.893100;0.774800;,
  0.898500;0.782900;,
  0.895100;0.789400;,
  0.836600;0.662600;,
  0.829100;0.658500;,
  0.827700;0.661900;,
  0.810400;0.648500;,
  0.804800;0.644800;,
  0.802900;0.647900;,
  0.909700;0.800400;,
  0.906000;0.799700;,
  0.905300;0.809200;,
  0.908800;0.809600;,
  0.907800;0.838000;,
  0.904200;0.832200;,
  0.904500;0.838600;,
  0.910900;0.785100;,
  0.906200;0.790700;,
  0.910500;0.791800;,
  0.916200;0.786600;,
  0.900000;0.691900;,
  0.901100;0.682900;,
  0.898300;0.683600;,
  0.915700;0.760800;,
  0.911300;0.757400;,
  0.910100;0.758700;,
  0.888100;0.830200;,
  0.887400;0.837200;,
  0.888700;0.837100;,
  0.101400;0.030200;,
  0.095100;0.029800;,
  0.095500;0.036200;,
  0.085600;0.051500;,
  0.085200;0.061300;,
  0.095100;0.060800;,
  0.094900;0.068500;,
  0.085100;0.069300;,
  0.076900;0.061500;,
  0.076900;0.069700;,
  0.088400;0.132900;,
  0.096500;0.133300;,
  0.096100;0.124800;,
  0.089100;0.141800;,
  0.095600;0.117200;,
  0.087100;0.117000;,
  0.087700;0.124300;,
  0.086300;0.101300;,
  0.086600;0.109800;,
  0.095300;0.109400;,
  0.079200;0.102400;,
  0.086000;0.088500;,
  0.085600;0.081600;,
  0.077900;0.082700;,
  0.078400;0.089700;,
  0.104600;0.133700;,
  0.096700;0.142000;,
  0.104400;0.142000;,
  0.111200;0.125900;,
  0.104400;0.125400;,
  0.111200;0.134300;,
  0.104000;0.108900;,
  0.111100;0.117600;,
  0.111200;0.108600;,
  0.104200;0.099000;,
  0.104600;0.090800;,
  0.111900;0.098300;,
  0.114400;0.087900;,
  0.112200;0.042200;,
  0.104600;0.043000;,
  0.105300;0.050800;,
  0.113600;0.050100;,
  0.086700;0.042700;,
  0.095300;0.051300;,
  0.095500;0.043200;,
  0.088000;0.035300;,
  0.888000;0.687800;,
  0.889700;0.696600;,
  0.895000;0.694300;,
  0.882800;0.689900;,
  0.895000;0.713200;,
  0.886800;0.708200;,
  0.889400;0.715800;,
  0.892300;0.705700;,
  0.900400;0.710700;,
  0.897600;0.703300;,
  0.895900;0.729100;,
  0.901600;0.726500;,
  0.898000;0.719800;,
  0.905100;0.743100;,
  0.905600;0.733300;,
  0.900000;0.735900;,
  0.910200;0.740200;,
  0.919200;0.742700;,
  0.915300;0.737300;,
  0.858900;0.673000;,
  0.850400;0.675100;,
  0.858500;0.679900;,
  0.919500;0.775100;,
  0.911900;0.779200;,
  0.917500;0.781000;,
  0.845700;0.686800;,
  0.854000;0.687300;,
  0.847700;0.682500;,
  0.862200;0.706900;,
  0.856900;0.708900;,
  0.862500;0.717900;,
  0.858200;0.699100;,
  0.867100;0.715600;,
  0.875400;0.721200;,
  0.871700;0.713400;,
  0.912700;0.695600;,
  0.915300;0.702400;,
  0.924800;0.697000;,
  0.918400;0.709100;,
  0.908000;0.706900;,
  0.922400;0.716400;,
  0.926600;0.723200;,
  0.935500;0.716400;,
  0.915100;0.721000;,
  0.911100;0.713700;,
  0.105300;0.060100;,
  0.105000;0.067700;,
  0.113800;0.066800;,
  0.113900;0.059300;,
  0.940800;0.737500;,
  0.932700;0.742500;,
  0.935500;0.744400;,
  0.938400;0.736000;,
  0.947100;0.728300;,
  0.104800;0.078900;,
  0.104800;0.085100;,
  0.113400;0.083600;,
  0.095000;0.080400;,
  0.104900;0.072900;,
  0.113500;0.077900;,
  0.115200;0.071000;,
  0.926100;0.755700;,
  0.918800;0.756900;,
  0.922900;0.759900;,
  0.922400;0.752900;,
  0.929300;0.751600;,
  0.926000;0.749100;,
  0.887500;0.681700;,
  0.882700;0.678400;,
  0.882400;0.683400;,
  0.872100;0.703500;,
  0.868600;0.694900;,
  0.867500;0.695500;,
  0.842600;0.692800;,
  0.848800;0.700700;,
  0.850600;0.698800;,
  0.900900;0.746100;,
  0.894400;0.739700;,
  0.899700;0.747200;,
  0.909500;0.769500;,
  0.902600;0.767300;,
  0.905200;0.776100;,
  0.868900;0.686500;,
  0.872800;0.679800;,
  0.866900;0.680100;,
  0.864900;0.687100;;
 }
}
