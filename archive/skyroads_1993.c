// Decompiled from SKYROADS_unpacked.EXE by Ghidra

// ---- FUN_1000_0000 @ 1000:0000 ----

void __cdecl16near FUN_1000_0000(void)

{
  code *pcVar1;
  undefined2 unaff_ES;
  undefined2 unaff_DS;
  
  pcVar1 = (code *)swi(0x10);
  (*pcVar1)();
  pcVar1 = (code *)swi(0x10);
  (*pcVar1)();
  pcVar1 = (code *)swi(0x10);
  (*pcVar1)();
  *(undefined1 **)0x3188 = &stack0xfffe;
  *(undefined2 *)0x318a = unaff_ES;
  pcVar1 = (code *)swi(0x10);
  (*pcVar1)();
  *(undefined1 **)0x318c = &stack0xfffe;
  *(undefined2 *)0x318e = unaff_ES;
  return;
}


// ---- FUN_1000_0046 @ 1000:0046 ----

void __cdecl16near FUN_1000_0046(void)

{
  FUN_1000_601d(3);
  FUN_1000_3b6b();
  FUN_1000_58a5();
  FUN_1000_5bc0();
  FUN_1000_6001(0);
  return;
}


// ---- FUN_1000_0069 @ 1000:0069 ----

void __cdecl16near FUN_1000_0069(void)

{
  undefined2 unaff_DS;
  
  if (*(int *)0x41aa != 0) {
    FUN_1000_601d(3);
    FUN_1000_3b6b();
    FUN_1000_58a5();
    if (*(int *)0x41aa == 8) {
      FUN_1000_5c82(0xcc2);
    }
    else {
      FUN_1000_5c82(0xcd4);
      FUN_1000_630f(*(undefined2 *)0x41aa,0);
    }
    FUN_1000_60e9();
  }
  return;
}


// ---- FUN_1000_00bb @ 1000:00bb ----

void __cdecl16near FUN_1000_00bb(void)

{
  undefined2 uVar1;
  int iVar2;
  int iVar3;
  undefined2 uVar4;
  uint uVar5;
  undefined2 unaff_DS;
  undefined4 local_6;
  
  uVar1 = FUN_1000_5c77(0xcfc);
  FUN_1000_6420(uVar1,0,0x1000,0);
  *(undefined2 *)0x54a8 = 0;
  while (*(int *)0x41aa == 0) {
    iVar2 = FUN_1000_6576();
    iVar3 = FUN_1000_6576();
    if (*(int *)0x41aa == 0) {
      if (*(int *)0x4560 == 0) {
        uVar4 = FUN_1000_3ef4(0x7d64,0);
        *(undefined2 *)0x4560 = uVar4;
        if ((*(int *)0x4560 + 0x7d7U & 0xf000) != (*(uint *)0x4560 & 0xf000)) {
          FUN_1000_3f72();
          *(undefined2 *)0x4560 = 0;
        }
      }
      uVar5 = FUN_1000_3ef4(iVar2,0);
      *(uint *)(*(int *)0x54a8 * 2 + 0xe76) = uVar5;
      local_6 = (int *)((ulong)uVar5 << 0x10);
      *local_6 = iVar2 - iVar3;
      if (*(int *)0x41aa == 0) {
        FUN_1000_66e6(iVar2 - iVar3,uVar5,iVar3);
      }
    }
    *(int *)0x54a8 = *(int *)0x54a8 + 1;
  }
  FUN_1000_5c11();
  FUN_1000_5c59(uVar1);
  return;
}


// ---- FUN_1000_019c @ 1000:019c ----

char __cdecl16near FUN_1000_019c(void)

{
  char cVar1;
  char cVar2;
  byte bVar3;
  char cVar4;
  
  cVar1 = in(0x40);
  cVar2 = in(0x40);
  bVar3 = in(0x41);
  cVar4 = in(0x41);
  return cVar4 + (cVar1 + cVar2 ^ bVar3);
}


// ---- FUN_1000_01b8 @ 1000:01b8 ----

void __cdecl16near FUN_1000_01b8(void)

{
  int *piVar1;
  bool bVar2;
  int iVar3;
  uint uVar4;
  undefined2 uVar5;
  int iVar6;
  undefined2 unaff_DS;
  uint local_8;
  
  local_8 = 0xffff;
  iVar3 = FUN_1000_603b();
  if (iVar3 == 0) {
    *(undefined2 *)0x3c = 0;
    iVar3 = FUN_1000_6027();
    if (iVar3 == 0) {
      FUN_1000_5c82(0xd08);
      return;
    }
  }
  FUN_1000_5a98();
  FUN_1000_58cd();
  FUN_1000_3acc();
  *(undefined2 *)0x4570 = 1;
  FUN_1000_0000();
  FUN_1000_5737();
  FUN_1000_57c4(0);
  FUN_1000_5508();
  FUN_1000_00bb();
  FUN_1000_0069();
  FUN_1000_2cce();
LAB_1000_0219:
  bVar2 = true;
  iVar3 = FUN_1000_4591();
  if (iVar3 == 0) {
    *(undefined2 *)0x95f6 = 3;
    goto LAB_1000_0251;
  }
LAB_1000_0232:
  *(undefined2 *)0x95f6 = *(undefined2 *)0x4518;
  FUN_1000_4e52(!bVar2);
LAB_1000_0251:
  bVar2 = false;
  FUN_1000_3f20();
  FUN_1000_5567();
  do {
    FUN_1000_3f20();
    if (*(int *)0x95f6 == 3) {
      uVar5 = FUN_1000_5614(0);
      *(undefined2 *)0x41c0 = uVar5;
      FUN_1000_5387(0);
    }
    else {
      iVar3 = FUN_1000_5180();
      if (iVar3 != 0) {
        FUN_1000_3f3b();
        FUN_1000_3f3b();
        goto LAB_1000_0232;
      }
      *(undefined2 *)0x95f6 = *(undefined2 *)0x4518;
      uVar4 = FUN_1000_019c();
      uVar4 = uVar4 % 9;
      if (uVar4 == local_8) {
        uVar4 = (uVar4 + 1) % 9;
      }
      FUN_1000_57c4(uVar4 + 1);
      uVar5 = FUN_1000_5614(*(int *)0x9332 + 1);
      *(undefined2 *)0x41c0 = uVar5;
      FUN_1000_5387(*(uint *)0x9332 / 3);
      local_8 = uVar4;
    }
    if (*(int *)0x3c != 0) {
      uVar5 = FUN_1000_3ef4(0xac80,0);
      *(undefined2 *)0x5478 = uVar5;
    }
    FUN_1000_0069();
    FUN_1000_0707();
    iVar3 = 0;
    for (uVar4 = 0; uVar4 < 0x1e; uVar4 = uVar4 + 1) {
      if (*(int *)(uVar4 * 2 + 0x451c) != 0) {
        iVar3 = iVar3 + 1;
      }
    }
    do {
      FUN_1000_4153();
      if ((*(int *)(*(int *)0x9332 * 2 + 0x451c) == 0) && (iVar3 == 0x1d)) {
        uVar5 = 1;
      }
      else {
        uVar5 = 0;
      }
      iVar6 = FUN_1000_2b3d(uVar5);
      if (*(int *)0x95f6 == 3) {
        FUN_1000_3f3b();
        FUN_1000_3f3b();
        if (iVar6 != 7) goto LAB_1000_0219;
        goto LAB_1000_0232;
      }
      if (iVar6 == 0) {
        piVar1 = (int *)(*(int *)0x9332 * 2 + 0x451c);
        *piVar1 = *piVar1 + 1;
        *(int *)0x9332 = *(int *)0x9332 + 1;
        FUN_1000_578c();
      }
    } while ((iVar6 != 7) && (iVar6 != 0));
    FUN_1000_3f3b();
  } while( true );
}


// ---- FUN_1000_03c2 @ 1000:03c2 ----

void __cdecl16near FUN_1000_03c2(int param_1)

{
  undefined2 uVar1;
  int iVar2;
  int iVar3;
  undefined1 *puVar4;
  byte bVar5;
  undefined2 unaff_DS;
  undefined4 local_8;
  
  *(undefined2 *)0xaf38 = *(undefined2 *)0x1600;
  if (*(int *)0x451a == 0) {
    if (*(int *)0xcb6 == 0) {
      bVar5 = in(0x61);
      out(0x61,bVar5 | 3);
      *(undefined2 *)0xbd0 = *(undefined2 *)(param_1 * 2 + 0x162);
    }
    else {
      uVar1 = *(undefined2 *)0x4560;
      iVar2 = *(int *)((param_1 + 1) * 2);
      iVar3 = *(int *)(param_1 * 2);
      puVar4 = (undefined1 *)*(undefined2 *)(param_1 * 2);
      local_8 = (undefined1 *)CONCAT22(uVar1,puVar4);
      FUN_1000_5bc0();
      FUN_1000_5b76(puVar4 + 1,uVar1,*local_8,(iVar2 - iVar3) + -1);
    }
  }
  return;
}


// ---- FUN_1000_0476 @ 1000:0476 ----

bool __cdecl16near FUN_1000_0476(void)

{
  undefined2 unaff_DS;
  bool bVar1;
  
  if (*(int *)0xcb6 == 0) {
    bVar1 = *(int *)*(undefined2 *)0xbd0 != 0;
  }
  else {
    bVar1 = *(uint *)0x1600 < *(int *)0xaf38 + 8U;
  }
  return bVar1;
}


// ---- FUN_1000_04c0 @ 1000:04c0 ----

undefined2 __cdecl16near FUN_1000_04c0(undefined2 param_1,undefined2 param_2,uint param_3)

{
  uint uVar1;
  int iVar2;
  undefined2 uVar3;
  undefined2 unaff_DS;
  undefined4 uVar4;
  
  uVar1 = param_3 / 0x80 - 0x5f;
  if (uVar1 < 0x142) {
    uVar4 = FUN_1000_5d8c(param_1,param_2,0x2000,0);
    uVar4 = FUN_1000_5d8c(uVar4,8,0);
    iVar2 = FUN_1000_5d4c(uVar4,0xe,0);
    uVar3 = *(undefined2 *)(iVar2 + 0x162c + (uVar1 / 0x2e) * 2);
  }
  else {
    uVar3 = 0;
  }
  return uVar3;
}


// ---- FUN_1000_0533 @ 1000:0533 ----

bool __cdecl16near FUN_1000_0533(undefined2 param_1,undefined2 param_2,uint param_3,int param_4)

{
  uint uVar1;
  undefined2 unaff_DS;
  uint local_6;
  
  uVar1 = FUN_1000_04c0(param_1,param_2,param_3);
  uVar1 = uVar1 & 0xf00;
  if (((uVar1 == 0x100) || (uVar1 == 0x300)) || (uVar1 == 0x500)) {
    local_6 = 0x17 - (param_3 / 0x80 - 0x31) % 0x2e;
    if ((0x7fff < local_6) || (local_6 == 0)) {
      local_6 = 1 - local_6;
    }
    if (local_6 < 0x26) {
      return (param_4 + 0xde00U) / 0x80 <
             (uint)(*(int *)(local_6 * 2 + 0x98) + *(int *)(local_6 * 2 + 0x4c)) / 2;
    }
  }
  return false;
}


// ---- FUN_1000_05f6 @ 1000:05f6 ----

int __cdecl16near FUN_1000_05f6(int param_1)

{
  undefined1 uVar1;
  undefined1 uVar2;
  undefined1 uVar3;
  undefined1 uVar4;
  byte bVar5;
  int iVar6;
  uint uVar7;
  uint uVar8;
  undefined2 unaff_DS;
  
  uVar1 = in(0x40);
  uVar2 = in(0x40);
  do {
    uVar3 = in(0x40);
    uVar4 = in(0x40);
    uVar7 = CONCAT11(uVar2,uVar1) - CONCAT11(uVar4,uVar3);
    if (CONCAT11(uVar2,uVar1) < CONCAT11(uVar4,uVar3)) {
      uVar7 = uVar7 + 0x19e4;
    }
  } while (uVar7 < 4000);
  uVar1 = in(0x40);
  uVar2 = in(0x40);
  uVar7 = CONCAT11(uVar2,uVar1);
  out(0x201,uVar1);
  while( true ) {
    uVar1 = in(0x40);
    uVar2 = in(0x40);
    uVar8 = uVar7 - CONCAT11(uVar2,uVar1);
    if (uVar7 < CONCAT11(uVar2,uVar1)) {
      uVar8 = uVar8 + 0x19e4;
    }
    if (6000 < uVar8) break;
    bVar5 = in(0x201);
    if (((byte)param_1 & bVar5) == 0) {
      uVar1 = in(0x40);
      uVar2 = in(0x40);
      iVar6 = uVar7 - CONCAT11(uVar2,uVar1);
      if (uVar7 < CONCAT11(uVar2,uVar1)) {
        iVar6 = iVar6 + 0x19e4;
      }
      return iVar6;
    }
  }
  if (param_1 == 1) {
    return *(int *)0x5172;
  }
  return *(int *)0x547c;
}


// ---- FUN_1000_0672 @ 1000:0672 ----

byte __cdecl16near FUN_1000_0672(void)

{
  undefined1 in_AL;
  byte bVar1;
  
  out(0x201,in_AL);
  bVar1 = in(0x201);
  return bVar1 >> 4 ^ 0xf;
}


// ---- FUN_1000_068b @ 1000:068b ----

void __cdecl16near FUN_1000_068b(void)

{
  code *pcVar1;
  
  pcVar1 = (code *)swi(0x33);
  (*pcVar1)();
  pcVar1 = (code *)swi(0x33);
  (*pcVar1)();
  pcVar1 = (code *)swi(0x33);
  (*pcVar1)();
  return;
}


// ---- FUN_1000_06a4 @ 1000:06a4 ----

void __cdecl16near FUN_1000_06a4(void)

{
  code *pcVar1;
  
  pcVar1 = (code *)swi(0x33);
  (*pcVar1)();
  return;
}


// ---- FUN_1000_06b9 @ 1000:06b9 ----

int __cdecl16near FUN_1000_06b9(int param_1)

{
  code *pcVar1;
  int in_CX;
  int extraout_DX;
  int in_BX;
  
  pcVar1 = (code *)swi(0x33);
  (*pcVar1)();
  if (((param_1 != 0) && (in_CX = extraout_DX, param_1 != 1)) && (in_CX = param_1, param_1 == 2)) {
    in_CX = in_BX;
  }
  return in_CX;
}


// ---- FUN_1000_0707 @ 1000:0707 ----

void __cdecl16near FUN_1000_0707(void)

{
  undefined2 uVar1;
  undefined2 unaff_DS;
  
  if (*(int *)0x95f6 == 1) {
    uVar1 = FUN_1000_05f6(1);
    *(undefined2 *)0x5172 = uVar1;
    uVar1 = FUN_1000_05f6(2);
    *(undefined2 *)0x547c = uVar1;
  }
  else if (*(int *)0x95f6 == 2) {
    FUN_1000_068b();
  }
  return;
}


// ---- FUN_1000_074c @ 1000:074c ----

void __cdecl16near FUN_1000_074c(void)

{
  uint uVar1;
  uint uVar2;
  undefined2 uVar3;
  int iVar4;
  undefined2 unaff_DS;
  
  iVar4 = *(int *)0x95f6;
  if (iVar4 == 0) {
    *(int *)0x95f4 =
         (uint)(((*(byte *)0xbd5 & 0x80) != 0 || (*(byte *)0xbd7 & 0x80) != 0) ||
               (*(byte *)0xbd9 & 0x80) != 0) -
         (uint)(((*(byte *)0xbd4 & 0x80) != 0 || (*(byte *)0xbd6 & 0x80) != 0) ||
               (*(byte *)0xbd8 & 0x80) != 0);
    *(int *)0x9330 =
         (uint)(((*(byte *)0xbd2 & 0x80) != 0 || (*(byte *)0xbd6 & 0x80) != 0) ||
               (*(byte *)0xbd7 & 0x80) != 0) -
         (uint)(((*(byte *)0xbd3 & 0x80) != 0 || (*(byte *)0xbd8 & 0x80) != 0) ||
               (*(byte *)0xbd9 & 0x80) != 0);
    *(uint *)0x547a = (uint)((*(byte *)0xbdb & 0x80) != 0);
  }
  else if (iVar4 == 1) {
    uVar1 = FUN_1000_05f6(1);
    uVar2 = FUN_1000_05f6(2);
    *(int *)0x95f4 =
         (uint)((uint)(((long)*(int *)0x5172 * 3 & 0xffffU) / 2) < uVar1) -
         (uint)(uVar1 < *(uint *)0x5172 / 2);
    *(int *)0x9330 =
         (uint)(uVar2 < *(uint *)0x547c / 2) -
         (uint)((uint)(((long)*(int *)0x547c * 3 & 0xffffU) / 2) < uVar2);
    uVar3 = FUN_1000_0672();
    *(undefined2 *)0x547a = uVar3;
  }
  else if (iVar4 == 2) {
    uVar1 = FUN_1000_06b9(0);
    uVar2 = FUN_1000_06b9(0);
    *(int *)0x95f4 = (uint)(0xaa < uVar2) - (uint)(uVar1 < 0x96);
    uVar1 = FUN_1000_06b9(1);
    uVar2 = FUN_1000_06b9(1);
    *(int *)0x9330 = (uint)(uVar2 < 0xf) - (uint)(0xb9 < uVar1);
    uVar3 = FUN_1000_06b9(2);
    *(undefined2 *)0x547a = uVar3;
    uVar3 = FUN_1000_06b9(1);
    FUN_1000_06a4(0xa0,uVar3);
  }
  else if (iVar4 == 3) {
    iVar4 = FUN_1000_5d8c(*(undefined2 *)0x9618,*(undefined2 *)0x961a,0x666,0);
    *(int *)0x9330 = (*(byte *)(iVar4 + -0x69e2) & 3) - 1;
    iVar4 = FUN_1000_5d8c(*(undefined2 *)0x9618,*(undefined2 *)0x961a,0x666,0);
    *(int *)0x95f4 = (*(byte *)(iVar4 + -0x69e2) >> 2 & 3) - 1;
    iVar4 = FUN_1000_5d8c(*(undefined2 *)0x9618,*(undefined2 *)0x961a,0x666,0);
    *(uint *)0x547a = *(byte *)(iVar4 + -0x69e2) >> 4 & 1;
  }
  return;
}


// ---- FUN_1000_0baf @ 1000:0baf ----

undefined2 __cdecl16near FUN_1000_0baf(int param_1,uint param_2)

{
  undefined2 uVar1;
  
  if ((param_1 < -0x162) || (param_2 < 0x2800)) {
    uVar1 = 2;
  }
  else if (param_1 < 0x163) {
    uVar1 = 0;
  }
  else {
    uVar1 = 1;
  }
  return uVar1;
}


// ---- FUN_1000_0be9 @ 1000:0be9 ----

int __cdecl16near FUN_1000_0be9(uint param_1)

{
  int iVar1;
  
  iVar1 = (int)(param_1 / 0x80 - 0x5f) / 0x2e;
  if (iVar1 < 0) {
    iVar1 = 0;
  }
  else if (6 < iVar1) {
    iVar1 = 6;
  }
  return iVar1;
}


// ---- FUN_1000_0c26 @ 1000:0c26 ----

undefined2 __cdecl16near
FUN_1000_0c26(undefined2 param_1,undefined2 param_2,undefined2 param_3,int param_4)

{
  uint uVar1;
  uint uVar2;
  undefined2 uVar3;
  undefined2 unaff_DS;
  
  uVar1 = FUN_1000_04c0(param_1,param_2,param_3);
  uVar2 = uVar1 & 0xf00;
  if ((uVar2 == 0) || (param_4 != 0)) {
    if ((uVar1 & 0xf) == 0) {
      uVar3 = 0;
    }
    else {
      uVar3 = 0x2800;
    }
  }
  else if (uVar2 == 0x100) {
    uVar3 = 0;
  }
  else {
    uVar3 = *(undefined2 *)((uVar2 >> 8) * 2 + 0xe4);
  }
  return uVar3;
}


// ---- FUN_1000_0c98 @ 1000:0c98 ----

void __cdecl16near FUN_1000_0c98(int param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  undefined2 uVar7;
  int iVar8;
  undefined2 unaff_DS;
  undefined2 uVar9;
  undefined2 uVar10;
  
  iVar1 = FUN_1000_0533(*(undefined2 *)0x9618,*(undefined2 *)0x961a,*(undefined2 *)0xaf1c,
                        *(undefined2 *)0xaf2c);
  if (*(int *)0x456a == 0) {
    if (*(int *)0x456e == 4) {
      iVar8 = 0;
    }
    else {
      iVar8 = *(int *)((int)(((ulong)*(uint *)0x1600 / 2) % 4) * 2 + 0x11a);
    }
    if (iVar1 == 0) {
      iVar2 = FUN_1000_0baf(*(undefined2 *)0x9336,*(undefined2 *)0xaf2c);
    }
    else {
      iVar2 = 0;
    }
    iVar3 = FUN_1000_0be9(*(undefined2 *)0xaf1c);
    uVar4 = (iVar3 * 3 + iVar2) * 3 + 0xe + iVar8;
  }
  else {
    uVar4 = *(uint *)0x456a / 3;
    if (0xd < uVar4) {
      uVar4 = 0xffff;
    }
  }
  uVar5 = FUN_1000_0c26(*(undefined2 *)0x9618,*(undefined2 *)0x961a,*(int *)0xaf1c + -0x380,iVar1);
  uVar6 = FUN_1000_0c26(*(undefined2 *)0x9618,*(undefined2 *)0x961a,*(int *)0xaf1c + 0x380,iVar1);
  if ((((*(int *)0xe1c != *(int *)0x9618) || (*(int *)0xe1e != *(int *)0x961a)) ||
      (*(int *)0xe20 != *(int *)0xaf1c)) ||
     (((*(int *)0xe22 != *(int *)0xaf2c || (*(uint *)0xe24 != uVar4)) ||
      (*(int *)0xe26 != *(int *)0x9334)))) {
    uVar9 = *(undefined2 *)0x961a;
    *(undefined2 *)0xe1c = *(undefined2 *)0x9618;
    *(undefined2 *)0xe1e = uVar9;
    *(undefined2 *)0xe20 = *(undefined2 *)0xaf1c;
    if (param_1 == 0) {
      iVar1 = *(int *)0xaf2c;
    }
    else {
      iVar1 = *(int *)0xaf2c + -0x80;
    }
    *(int *)0xe22 = iVar1;
    *(uint *)0xe24 = uVar4;
    *(undefined2 *)0xe26 = *(undefined2 *)0x9334;
    if (*(int *)0x3c == 0) {
      iVar1 = (uint)(*(int *)0x9334 == 0) * 0x200 + -0x6000;
    }
    else {
      iVar1 = *(int *)0x5478;
    }
    if (*(int *)0x456a == 0) {
      if (uVar5 < uVar6) {
        uVar5 = uVar6;
      }
      uVar5 = (*(int *)0xaf2c - uVar5) / 0x80;
    }
    else {
      uVar5 = 0x7fff;
    }
    uVar10 = 0;
    uVar9 = *(undefined2 *)0xaf36;
    iVar8 = *(int *)0xaf34 + uVar4 * 0x2d0;
    if (uVar4 == 0xffff) {
      uVar4 = 0;
    }
    else {
      uVar4 = *(uint *)0xe22 / 0x80;
    }
    uVar7 = FUN_1000_5d8c(*(undefined2 *)0x9618,*(undefined2 *)0x961a,0x2000,0);
    iVar1 = FUN_1000_0be9(*(undefined2 *)0xaf1c,uVar7,uVar4,iVar8,uVar9,uVar10,uVar5,iVar1);
    FUN_1000_2d1f(*(uint *)0xaf1c / 0x80 + *(int *)(iVar1 * 2 + 0x3e));
    *(uint *)0x9334 = *(uint *)0x9334 ^ 1;
  }
  return;
}


// ---- FUN_1000_0ed0 @ 1000:0ed0 ----

void __cdecl16near FUN_1000_0ed0(void)

{
  code *pcVar1;
  undefined2 unaff_DS;
  
  if (*(int *)0x3c == 0) {
    pcVar1 = (code *)swi(0x10);
    (*pcVar1)();
  }
  return;
}


// ---- FUN_1000_0eeb @ 1000:0eeb ----

void __cdecl16near FUN_1000_0eeb(void)

{
  undefined2 unaff_DS;
  
  do {
  } while (*(int *)0x1600 == *(int *)0x1600);
  return;
}


// ---- FUN_1000_0f05 @ 1000:0f05 ----

undefined2 __cdecl16near FUN_1000_0f05(void)

{
  uint *puVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  undefined2 unaff_DS;
  
  *(undefined2 *)0xaf2c = 0;
  *(undefined2 *)0x1600 = 0;
  while( true ) {
    if (0x47 < *(uint *)0x1600) {
      return 0;
    }
    if ((*(byte *)0xbda & 0x80) != 0) break;
    FUN_1000_0c98(0);
    FUN_1000_0eeb();
    FUN_1000_0ed0();
    uVar3 = *(uint *)0x54ac;
    iVar4 = *(int *)0x54ae;
    puVar1 = (uint *)0x9618;
    uVar2 = *puVar1;
    *puVar1 = *puVar1 + uVar3;
    *(int *)0x961a = *(int *)0x961a + iVar4 + (uint)CARRY2(uVar2,uVar3);
  }
  return 7;
}


// ---- FUN_1000_0f62 @ 1000:0f62 ----

void __cdecl16near FUN_1000_0f62(char *param_1,int param_2,undefined1 param_3,undefined1 param_4)

{
  char *pcVar1;
  undefined1 *puVar2;
  undefined2 uVar3;
  undefined1 uVar4;
  char *pcVar5;
  undefined1 *puVar6;
  undefined2 unaff_DS;
  
  uVar3 = *(undefined2 *)0xaf2a;
  puVar6 = (undefined1 *)0x0;
  pcVar5 = (char *)param_1;
  do {
    pcVar1 = pcVar5;
    pcVar5 = pcVar5 + 1;
    uVar4 = 0;
    if ((*pcVar1 != '\0') && (uVar4 = param_3, *pcVar1 != '\x01')) {
      uVar4 = param_4;
    }
    puVar2 = puVar6;
    puVar6 = puVar6 + 1;
    *puVar2 = uVar4;
    param_2 = param_2 + -1;
  } while (param_2 != 0);
  return;
}


// ---- FUN_1000_0f8c @ 1000:0f8c ----

void __cdecl16near FUN_1000_0f8c(undefined2 *param_1,int param_2)

{
  undefined2 uVar1;
  undefined2 *puVar2;
  undefined2 uVar3;
  undefined2 uVar4;
  undefined2 unaff_DS;
  undefined2 local_10;
  undefined2 local_e;
  uint local_c;
  uint local_a;
  int local_8;
  
  if (*(int *)0x3c == 0) {
    uVar3 = 0;
    if (param_2 == 0) {
      uVar1 = 8;
    }
    else {
      uVar1 = 5;
    }
  }
  else if (param_2 == 0) {
    uVar3 = 0x5c;
    uVar1 = 0x5d;
  }
  else {
    uVar3 = 0x5e;
    uVar1 = 0x5f;
  }
  local_10 = *(undefined2 *)0xaf2a;
  local_e = *param_1;
  uVar4 = (undefined2)((ulong)param_1 >> 0x10);
  puVar2 = (undefined2 *)param_1;
  local_a = (uint)*(byte *)(puVar2 + 1);
  local_c = (uint)*(byte *)((int)puVar2 + 3);
  local_8 = local_a * local_c;
  FUN_1000_0f62(puVar2 + 2,uVar4,local_8,uVar3,uVar1);
  if (*(int *)0x3c == 0) {
    FUN_1000_3c9a();
  }
  FUN_1000_417e(0,0xa000,0,1);
  FUN_1000_4201(&local_10);
  if (*(int *)0x3c == 0) {
    FUN_1000_417e(0,0xa200,0,1);
    FUN_1000_4201(&local_10);
  }
  return;
}


// ---- FUN_1000_1073 @ 1000:1073 ----

void __cdecl16near
FUN_1000_1073(int param_1,int param_2,undefined2 param_3,undefined2 param_4,undefined2 param_5)

{
  undefined2 unaff_DS;
  undefined2 local_e;
  int local_c;
  undefined2 local_a;
  undefined2 local_8;
  
  FUN_1000_0f62(param_5);
  local_e = *(undefined2 *)0xaf2a;
  local_c = param_2 * 0x140 + param_1;
  local_8 = param_3;
  local_a = param_4;
  if (*(int *)0x3c == 0) {
    FUN_1000_3c9a();
  }
  FUN_1000_417e(0,0xa000,0,0);
  FUN_1000_4201(&local_e);
  if (*(int *)0x3c == 0) {
    FUN_1000_417e(0,0xa200,0,0);
    FUN_1000_4201(&local_e);
  }
  return;
}


// ---- FUN_1000_1114 @ 1000:1114 ----

void __cdecl16near FUN_1000_1114(int param_1,undefined2 param_2,uint param_3,uint param_4)

{
  int iVar1;
  uint uVar2;
  undefined2 unaff_DS;
  
  for (uVar2 = 0; (uVar2 < param_4 && ((param_3 != 0 || (uVar2 == 0)))); uVar2 = uVar2 + 1) {
    iVar1 = (int)(((ulong)param_3 / (ulong)*(uint *)(uVar2 * 2 + 0x338)) % 10);
    FUN_1000_1073(((param_4 - uVar2) + -1) * 5 + param_1,param_2,4,5,iVar1 * 0x14 + 0x16c);
    param_3 = param_3 - iVar1 * *(int *)(uVar2 * 2 + 0x338);
  }
  return;
}


// ---- FUN_1000_1191 @ 1000:1191 ----

uint __cdecl16near FUN_1000_1191(int param_1,int param_2)

{
  uint uVar1;
  undefined2 unaff_DS;
  
  if (*(int *)0x3c == 0) {
    uVar1 = FUN_1000_3e4c(param_1,param_2);
  }
  else {
    uVar1 = (uint)*(byte *)(param_2 * 0x140 + param_1);
  }
  return uVar1;
}


// ---- FUN_1000_11d3 @ 1000:11d3 ----

void __cdecl16near FUN_1000_11d3(int param_1,int param_2,undefined2 param_3)

{
  undefined2 unaff_DS;
  
  if (*(int *)0x3c == 0) {
    FUN_1000_3e0f(param_1,param_2,param_3);
  }
  else {
    *(undefined1 *)(param_2 * 0x140 + param_1) = (char)param_3;
  }
  return;
}


// ---- FUN_1000_1218 @ 1000:1218 ----

void __cdecl16near FUN_1000_1218(int param_1)

{
  int iVar1;
  int iVar2;
  undefined2 uVar3;
  int iVar4;
  undefined2 unaff_DS;
  
  param_1 = param_1 + 0x2a;
  iVar4 = 0x8f;
  iVar1 = FUN_1000_1191(param_1,0x8f);
  while (iVar2 = FUN_1000_1191(param_1,iVar4), iVar2 == iVar1) {
    iVar4 = iVar4 + -1;
  }
  while( true ) {
    iVar4 = iVar4 + 1;
    iVar2 = FUN_1000_1191(param_1,iVar4);
    if (iVar2 != iVar1) break;
    if (*(int *)0x3c == 0) {
      uVar3 = 6;
    }
    else {
      uVar3 = 0x60;
    }
    FUN_1000_11d3(param_1,iVar4,uVar3);
  }
  return;
}


// ---- FUN_1000_1282 @ 1000:1282 ----

void __cdecl16near
FUN_1000_1282(uint param_1,uint param_2,int param_3,int param_4,int param_5,int param_6)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  
  for (uVar2 = param_1; uVar3 = param_2, uVar2 < param_1 + param_3; uVar2 = uVar2 + 1) {
    for (; uVar3 < param_2 + param_4; uVar3 = uVar3 + 1) {
      iVar1 = FUN_1000_1191(uVar2,uVar3);
      if (iVar1 == param_5) {
        FUN_1000_11d3(uVar2,uVar3,param_6);
      }
      else if (iVar1 == param_6) {
        FUN_1000_11d3(uVar2,uVar3,param_5);
      }
    }
  }
  return;
}


// ---- FUN_1000_12f8 @ 1000:12f8 ----

void __cdecl16near FUN_1000_12f8(void)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  undefined2 uVar4;
  undefined2 uVar5;
  uint uVar6;
  undefined2 unaff_DS;
  undefined4 uVar7;
  uint local_e;
  uint local_c;
  uint local_a;
  uint local_8;
  
  uVar2 = (uint)(4 < *(uint *)0x1600 % 9);
  local_8 = FUN_1000_5e5a(*(uint *)0x54ac - *(uint *)0xaf2e,
                          (*(int *)0x54ae - *(int *)0xaf30) -
                          (uint)(*(uint *)0x54ac < *(uint *)0xaf2e),0x141,0);
  if (0x22 < local_8) {
    local_8 = 0x22;
  }
  uVar6 = local_8;
  if (*(uint *)0x41be < local_8) {
    uVar6 = *(uint *)0x41be;
  }
  while( true ) {
    uVar3 = local_8;
    if (local_8 < *(uint *)0x41be) {
      uVar3 = *(uint *)0x41be;
    }
    if (uVar3 <= uVar6) break;
    FUN_1000_0f8c(*(int *)0x54a4 + *(int *)(uVar6 * 2 + 0x4572),*(undefined2 *)0x54a6,
                  *(uint *)0x41be < local_8);
    uVar6 = uVar6 + 1;
  }
  *(uint *)0x41be = local_8;
  local_a = (*(int *)0xb13c + 2999U) / 3000;
  if (10 < local_a) {
    local_a = 10;
  }
  uVar6 = local_a;
  if (*(uint *)0x456c < local_a) {
    uVar6 = *(uint *)0x456c;
  }
  while( true ) {
    uVar3 = local_a;
    if (local_a < *(uint *)0x456c) {
      uVar3 = *(uint *)0x456c;
    }
    if (uVar3 <= uVar6) break;
    FUN_1000_0f8c(*(int *)0x5474 + *(int *)(uVar6 * 2 + -0x6a08),*(undefined2 *)0x5476,
                  *(uint *)0x456c < local_a);
    uVar6 = uVar6 + 1;
  }
  *(uint *)0x456c = local_a;
  if ((*(int *)0x456e == 5) && (uVar2 != *(uint *)0xaf1e)) {
    if (*(int *)0x3c == 0) {
      uVar4 = 4;
    }
    else {
      uVar4 = 100;
    }
    if (*(int *)0x3c == 0) {
      uVar5 = 0xf;
    }
    else {
      uVar5 = 99;
    }
    FUN_1000_1282(0xa0,0xa1,7,7,uVar5,uVar4);
    if (uVar2 != 0) {
      FUN_1000_03c2(3);
    }
  }
  local_c = (*(int *)0x5494 + 2999U) / 3000;
  if (10 < local_c) {
    local_c = 10;
  }
  uVar6 = local_c;
  if (*(uint *)0x960c < local_c) {
    uVar6 = *(uint *)0x960c;
  }
  while( true ) {
    uVar3 = local_c;
    if (local_c < *(uint *)0x960c) {
      uVar3 = *(uint *)0x960c;
    }
    if (uVar3 <= uVar6) break;
    FUN_1000_0f8c(*(int *)0x960e + *(int *)(uVar6 * 2 + 0x5480),*(undefined2 *)0x9610,
                  *(uint *)0x960c < local_c);
    uVar6 = uVar6 + 1;
  }
  *(uint *)0x960c = local_c;
  if ((*(int *)0x456e == 4) && (uVar2 != *(uint *)0xaf1e)) {
    if (*(int *)0x3c == 0) {
      uVar4 = 4;
    }
    else {
      uVar4 = 100;
    }
    if (*(int *)0x3c == 0) {
      uVar5 = 0xf;
    }
    else {
      uVar5 = 99;
    }
    FUN_1000_1282(0x9b,0xa9,0x10,5,uVar5,uVar4);
    if (uVar2 != 0) {
      FUN_1000_03c2(3);
    }
  }
  uVar4 = *(undefined2 *)0x9618;
  iVar1 = *(int *)0x961a;
  uVar7 = FUN_1000_5d80();
  uVar7 = FUN_1000_5e5a((int)uVar7,(int)((ulong)uVar7 >> 0x10) + -3,0x1e,0);
  local_e = FUN_1000_5d8c(uVar4,iVar1 + -3,uVar7);
  if (0x1d < local_e) {
    local_e = 0x1d;
  }
  for (uVar6 = *(uint *)0x455c; uVar6 < local_e; uVar6 = uVar6 + 1) {
    FUN_1000_1218(uVar6);
  }
  *(uint *)0x455c = local_e;
  if (*(int *)0xaf20 != *(int *)0x455a) {
    FUN_1000_1073(0xcb,0x9c,0x1a,5,*(int *)0x455a * 0x82 + 0x234);
  }
  *(undefined2 *)0xaf20 = *(undefined2 *)0x455a;
  *(uint *)0xaf1e = uVar2;
  return;
}


// ---- FUN_1000_1631 @ 1000:1631 ----

uint __cdecl16near FUN_1000_1631(uint param_1,uint param_2,uint param_3)

{
  uint uVar1;
  undefined2 unaff_DS;
  
  if (param_2 < 0x26) {
    uVar1 = (param_3 + 0xde00) / 0x80;
    param_1 = param_1 & 0xf00;
    if (param_1 == 0x100) {
      if ((uVar1 < *(uint *)(param_2 * 2 + 0x98)) && (*(uint *)(param_2 * 2 + 0x4c) <= uVar1)) {
        param_1 = 1;
      }
      else {
        param_1 = 0;
      }
    }
    else if (param_1 == 0x200) {
      param_1 = (uint)(param_3 < 0x3200);
    }
    else if (param_1 == 0x300) {
      if ((param_3 < 0x3200) && (*(uint *)(param_2 * 2 + 0x4c) <= uVar1)) {
        param_1 = 1;
      }
      else {
        param_1 = 0;
      }
    }
    else if (param_1 == 0x400) {
      param_1 = (uint)(param_3 < 0x3c00);
    }
    else if (param_1 == 0x500) {
      if ((param_3 < 0x3c00) && (*(uint *)(param_2 * 2 + 0x4c) <= uVar1)) {
        param_1 = 1;
      }
      else {
        param_1 = 0;
      }
    }
  }
  else {
    param_1 = 0;
  }
  return param_1;
}


// ---- FUN_1000_1732 @ 1000:1732 ----

undefined2 __cdecl16near
FUN_1000_1732(undefined2 param_1,undefined2 param_2,uint param_3,uint param_4)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  undefined2 uVar4;
  int local_c;
  uint local_a;
  
  uVar1 = FUN_1000_04c0(param_1,param_2,param_3 + 0x700);
  uVar2 = FUN_1000_04c0(param_1,param_2,param_3 - 0x700);
  if (((((uVar1 & 0xf) != 0) || ((uVar2 & 0xf) != 0)) && (param_4 < 0x2800)) &&
     (0x2480 < param_4 + 0x600)) {
    return 1;
  }
  if ((param_4 + 0x680 < 0x2801) || (((uVar2 & 0xf00) == 0 && ((uVar1 & 0xf00) == 0)))) {
LAB_1000_1861:
    uVar4 = 0;
  }
  else {
    uVar4 = FUN_1000_04c0(param_1,param_2,param_3);
    local_a = 0x17 - (param_3 / 0x80 - 0x31) % 0x2e;
    local_c = -0x1700;
    if ((0x7fff < local_a) || (local_a == 0)) {
      local_a = 1 - local_a;
      local_c = 0x1700;
    }
    iVar3 = FUN_1000_1631(uVar4,local_a,param_4);
    if (iVar3 == 0) {
      uVar4 = FUN_1000_04c0(param_1,param_2,param_3 + local_c,0x2f - local_a,param_4);
      iVar3 = FUN_1000_1631(uVar4);
      if (iVar3 == 0) goto LAB_1000_1861;
    }
    uVar4 = 1;
  }
  return uVar4;
}


// ---- FUN_1000_186b @ 1000:186b ----

/* WARNING: Removing unreachable block (ram,0x000119ba) */

void __cdecl16near FUN_1000_186b(uint param_1,int param_2,uint param_3,uint param_4)

{
  uint *puVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  undefined2 unaff_DS;
  undefined4 uVar7;
  ulong uVar8;
  uint local_a;
  int local_8;
  
  if ((((*(uint *)0x9618 != param_1) || (*(int *)0x961a != param_2)) || (*(uint *)0xaf1c != param_3)
      ) || (*(uint *)0xaf2c != param_4)) {
    for (uVar6 = 1; uVar6 < 6; uVar6 = uVar6 + 1) {
      iVar3 = (int)((param_4 - *(int *)0xaf2c) * uVar6) / 5 + *(int *)0xaf2c;
      iVar4 = (int)((param_3 - *(int *)0xaf1c) * uVar6) / 5 + *(int *)0xaf1c;
      uVar7 = FUN_1000_5d4c(param_1 - *(uint *)0x9618,
                            (param_2 - *(int *)0x961a) - (uint)(param_1 < *(uint *)0x9618),uVar6,0);
      uVar7 = FUN_1000_5e5a(uVar7,5,0);
      iVar3 = FUN_1000_1732((uint)uVar7 + *(uint *)0x9618,
                            (int)((ulong)uVar7 >> 0x10) + *(int *)0x961a +
                            (uint)CARRY2((uint)uVar7,*(uint *)0x9618),iVar4,iVar3);
      if (iVar3 != 0) break;
    }
    uVar7 = FUN_1000_5d4c(param_1 - *(uint *)0x9618,
                          (param_2 - *(int *)0x961a) - (uint)(param_1 < *(uint *)0x9618),uVar6 - 1,0
                         );
    uVar7 = FUN_1000_5e5a(uVar7,5,0);
    puVar1 = (uint *)0x9618;
    uVar2 = *puVar1;
    *puVar1 = *puVar1 + (uint)uVar7;
    *(int *)0x961a = *(int *)0x961a + (int)((ulong)uVar7 >> 0x10) + (uint)CARRY2(uVar2,(uint)uVar7);
    *(int *)0xaf1c = *(int *)0xaf1c + (int)((param_3 - *(int *)0xaf1c) * (uVar6 - 1)) / 5;
    *(int *)0xaf2c = *(int *)0xaf2c + (int)((param_4 - *(int *)0xaf2c) * (uVar6 - 1)) / 5;
    uVar8 = 0x1000;
    while( true ) {
      local_8 = (int)(uVar8 >> 0x10);
      local_a = (uint)uVar8;
      if (uVar8 == 0) break;
      while ((uVar8 <= CONCAT22((param_2 - *(int *)0x961a) - (uint)(param_1 < *(uint *)0x9618),
                                param_1 - *(uint *)0x9618) &&
             (iVar3 = FUN_1000_1732(uVar8 + CONCAT22(*(undefined2 *)0x961a,*(undefined2 *)0x9618),
                                    *(undefined2 *)0xaf1c,*(undefined2 *)0xaf2c), iVar3 == 0))) {
        puVar1 = (uint *)0x9618;
        uVar6 = *puVar1;
        *puVar1 = *puVar1 + local_a;
        *(int *)0x961a = *(int *)0x961a + local_8 + (uint)CARRY2(uVar6,local_a);
      }
      uVar8 = FUN_1000_5d8c(uVar8,0x10,0);
    }
    if (*(uint *)0xaf1c < param_3) {
      iVar3 = 0x7d;
    }
    else {
      iVar3 = -0x7d;
    }
    for (; iVar3 != 0; iVar3 = iVar3 / 5) {
      while( true ) {
        if ((int)(param_3 - *(int *)0xaf1c) < 1) {
          iVar4 = -(param_3 - *(int *)0xaf1c);
        }
        else {
          iVar4 = param_3 - *(int *)0xaf1c;
        }
        iVar5 = iVar3;
        if (iVar3 < 1) {
          iVar5 = -iVar3;
        }
        if ((iVar4 < iVar5) ||
           (iVar4 = FUN_1000_1732(*(undefined2 *)0x9618,*(undefined2 *)0x961a,iVar3 + *(int *)0xaf1c
                                  ,*(undefined2 *)0xaf2c), iVar4 != 0)) break;
        *(int *)0xaf1c = *(int *)0xaf1c + iVar3;
      }
    }
    if (*(uint *)0xaf2c < param_4) {
      iVar3 = 0x7d;
    }
    else {
      iVar3 = -0x7d;
    }
    for (; iVar3 != 0; iVar3 = iVar3 / 5) {
      while( true ) {
        if ((int)(param_4 - *(int *)0xaf2c) < 1) {
          iVar4 = -(param_4 - *(int *)0xaf2c);
        }
        else {
          iVar4 = param_4 - *(int *)0xaf2c;
        }
        iVar5 = iVar3;
        if (iVar3 < 1) {
          iVar5 = -iVar3;
        }
        if ((iVar4 < iVar5) ||
           (iVar4 = FUN_1000_1732(*(undefined2 *)0x9618,*(undefined2 *)0x961a,*(undefined2 *)0xaf1c,
                                  iVar3 + *(int *)0xaf2c), iVar4 != 0)) break;
        *(int *)0xaf2c = *(int *)0xaf2c + iVar3;
      }
    }
  }
  return;
}


// ---- FUN_1000_1b49 @ 1000:1b49 ----

void __cdecl16near FUN_1000_1b49(uint param_1)

{
  uint *puVar1;
  uint uVar2;
  undefined2 unaff_DS;
  
  param_1 = param_1 & 0xf;
  if (param_1 == 2) {
    if (*(int *)0x456a == 0) {
      puVar1 = (uint *)0x54ac;
      uVar2 = *puVar1;
      *puVar1 = *puVar1 - 0x12f;
      *(int *)0x54ae = *(int *)0x54ae - (uint)(uVar2 < 0x12f);
    }
  }
  else if (param_1 == 9) {
    if (*(int *)0x456e == 0) {
      if ((*(uint *)0x5494 < 27000) || (*(uint *)0xb13c < 27000)) {
        FUN_1000_03c2(4);
      }
      *(undefined2 *)0x5494 = 30000;
      *(undefined2 *)0xb13c = 30000;
    }
  }
  else if (param_1 == 10) {
    if (*(int *)0x456a == 0) {
      puVar1 = (uint *)0x54ac;
      uVar2 = *puVar1;
      *puVar1 = *puVar1 + 0x12f;
      *(int *)0x54ae = *(int *)0x54ae + (uint)(0xfed0 < uVar2);
    }
  }
  else if (param_1 == 0xc) {
    if (*(int *)0x456e == 0) {
      *(undefined2 *)0x456e = 2;
    }
    if (*(int *)0x456a == 0) {
      *(undefined2 *)0x456a = 1;
      FUN_1000_03c2(0);
    }
  }
  if ((*(int *)0x54ae < 1) && (*(int *)0x54ae < 0)) {
    *(undefined2 *)0x54ac = 0;
    *(undefined2 *)0x54ae = 0;
  }
  else if ((-1 < *(int *)0x54ae) && ((0 < *(int *)0x54ae || (0x2aaa < *(uint *)0x54ac)))) {
    *(undefined2 *)0x54ac = 0x2aaa;
    *(undefined2 *)0x54ae = 0;
  }
  return;
}


// ---- FUN_1000_1c62 @ 1000:1c62 ----

undefined2 __cdecl16near FUN_1000_1c62(undefined2 param_1,undefined2 param_2,undefined2 param_3)

{
  uint uVar1;
  uint uVar2;
  undefined2 uVar3;
  
  uVar1 = FUN_1000_04c0(param_1,param_2,param_3);
  uVar2 = uVar1 & 0xf00;
  if (uVar2 != 0) {
    if (uVar2 == 0x100) {
      return 0;
    }
    uVar1 = uVar1 >> 4;
  }
  if ((((uVar1 & 0xf) == 0) && (uVar2 == 0)) || ((uVar1 & 0xf) == 0xc)) {
    uVar3 = 1;
  }
  else {
    uVar3 = 0;
  }
  return uVar3;
}


// ---- FUN_1000_1ccd @ 1000:1ccd ----

/* WARNING: Removing unreachable block (ram,0x00011d9e) */

undefined2 __cdecl16near
FUN_1000_1ccd(undefined2 param_1,undefined2 param_2,uint param_3,uint param_4,undefined2 param_5,
             undefined2 param_6,int param_7,int param_8)

{
  long lVar1;
  long lVar2;
  long lVar3;
  int iVar4;
  int iVar5;
  undefined2 uVar6;
  uint uVar7;
  undefined2 unaff_DS;
  undefined4 uVar8;
  long lVar9;
  
  lVar1 = CONCAT22(param_6,param_5);
  lVar2 = CONCAT22(param_2,param_1);
  do {
    lVar3 = lVar2;
    uVar7 = param_3;
    param_8 = param_8 + *(int *)0x54aa;
    lVar2 = lVar1 + lVar3;
    iVar5 = *(int *)0x5496;
    uVar8 = FUN_1000_5d4c(lVar1 + 0x618,param_7,param_7 >> 0xf);
    iVar4 = FUN_1000_5e5a(uVar8,0x200,0);
    param_3 = uVar7 + iVar4 + iVar5;
    if ((param_3 < 0x2f80) || (0xd080 < param_3)) {
      return 0;
    }
    param_4 = param_4 + param_8;
    lVar9 = FUN_1000_5d4c(*(int *)0x9330,*(int *)0x9330 >> 0xf,0x4b,0);
    lVar1 = lVar9 + lVar1;
    if ((lVar1 < 0x10000) && (lVar1 < 0)) {
      lVar1 = 0;
    }
    else if (0x2aaa < lVar1) {
      lVar1 = 0x2aaa;
    }
  } while (0x2800 < param_4);
  iVar5 = FUN_1000_1c62(lVar3,uVar7);
  if ((iVar5 == 0) && (iVar5 = FUN_1000_1c62(lVar2,param_3), iVar5 == 0)) {
    uVar6 = 1;
  }
  else {
    uVar6 = 0;
  }
  return uVar6;
}


// ---- FUN_1000_1dfa @ 1000:1dfa ----

void __cdecl16near FUN_1000_1dfa(void)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  undefined2 unaff_DS;
  undefined4 uVar8;
  long lVar9;
  undefined2 uVar10;
  undefined2 uVar11;
  
  iVar4 = FUN_1000_1ccd(*(undefined2 *)0x9618,*(undefined2 *)0x961a,*(undefined2 *)0xaf1c,
                        *(undefined2 *)0xaf2c,*(undefined2 *)0x54ac,*(undefined2 *)0x54ae,
                        *(undefined2 *)0x4568,*(undefined2 *)0x9336);
  if (iVar4 == 0) {
    uVar1 = *(uint *)0x54ac;
    iVar4 = *(int *)0x54ae;
    iVar3 = *(int *)0x4568;
    for (iVar7 = 1; iVar7 < 7; iVar7 = iVar7 + 1) {
      uVar11 = *(undefined2 *)0x9336;
      iVar5 = (iVar3 * iVar7) / 10 + iVar3;
      *(int *)0x4568 = iVar5;
      iVar5 = FUN_1000_1ccd(*(undefined2 *)0x9618,*(undefined2 *)0x961a,*(undefined2 *)0xaf1c,
                            *(undefined2 *)0xaf2c,*(undefined2 *)0x54ac,*(undefined2 *)0x54ae,iVar5,
                            uVar11);
      if (iVar5 != 0) break;
      uVar11 = *(undefined2 *)0x9336;
      iVar5 = iVar3 - (iVar3 * iVar7) / 10;
      *(int *)0x4568 = iVar5;
      iVar5 = FUN_1000_1ccd(*(undefined2 *)0x9618,*(undefined2 *)0x961a,*(undefined2 *)0xaf1c,
                            *(undefined2 *)0xaf2c,*(undefined2 *)0x54ac,*(undefined2 *)0x54ae,iVar5,
                            uVar11);
      if (iVar5 != 0) break;
      *(int *)0x4568 = iVar3;
      uVar8 = FUN_1000_5d4c(uVar1,iVar4,iVar7,iVar7 >> 0xf);
      lVar9 = FUN_1000_5e5a(uVar8,10,0);
      lVar9 = lVar9 + CONCAT22(iVar4,uVar1);
      *(undefined2 *)0x54ac = (int)lVar9;
      *(undefined2 *)0x54ae = (int)((ulong)lVar9 >> 0x10);
      if ((*(int *)0x54ae < 1) &&
         (((*(int *)0x54ae < 0 || (*(uint *)0x54ac < 0x2aaa)) &&
          (iVar5 = FUN_1000_1ccd(*(undefined2 *)0x9618,*(undefined2 *)0x961a,*(undefined2 *)0xaf1c,
                                 *(undefined2 *)0xaf2c,*(undefined2 *)0x54ac,*(undefined2 *)0x54ae,
                                 *(undefined2 *)0x4568,*(undefined2 *)0x9336), iVar5 != 0)))) break;
      uVar11 = *(undefined2 *)0x9336;
      uVar10 = *(undefined2 *)0x4568;
      uVar8 = FUN_1000_5d4c(uVar1,iVar4,iVar7,iVar7 >> 0xf);
      uVar8 = FUN_1000_5e5a(uVar8,10,0);
      iVar5 = uVar1 - (uint)uVar8;
      iVar6 = (iVar4 - (int)((ulong)uVar8 >> 0x10)) - (uint)(uVar1 < (uint)uVar8);
      *(int *)0x54ac = iVar5;
      *(int *)0x54ae = iVar6;
      iVar5 = FUN_1000_1ccd(*(undefined2 *)0x9618,*(undefined2 *)0x961a,*(undefined2 *)0xaf1c,
                            *(undefined2 *)0xaf2c,iVar5,iVar6,uVar10,uVar11);
      if (iVar5 != 0) break;
      *(uint *)0x54ac = uVar1;
      *(int *)0x54ae = iVar4;
    }
    uVar2 = *(uint *)0x54ac;
    iVar3 = *(int *)0x54ae;
    *(int *)0xaf2e = uVar2 - uVar1;
    *(int *)0xaf30 = (iVar3 - iVar4) - (uint)(uVar2 < uVar1);
    if (iVar7 < 7) {
      *(undefined2 *)0x455a = 1;
    }
  }
  return;
}


// ---- FUN_1000_1fd9 @ 1000:1fd9 ----

undefined2 __cdecl16near FUN_1000_1fd9(void)

{
  uint *puVar1;
  uint uVar2;
  bool bVar3;
  bool bVar4;
  bool bVar5;
  int iVar6;
  undefined2 uVar7;
  int iVar8;
  uint uVar9;
  undefined2 unaff_DS;
  bool bVar10;
  bool bVar11;
  bool bVar12;
  undefined4 uVar13;
  long lVar14;
  int local_24;
  uint local_22;
  int local_20;
  int local_1e;
  uint local_1c;
  uint local_1a;
  uint local_18;
  uint local_16;
  int local_c;
  uint local_4;
  
  if (*(int *)0x95f6 == 2) {
    FUN_1000_06a4(0xa0,100);
  }
  *(undefined2 *)0x516e = 0;
  uVar13 = FUN_1000_5d4c(*(undefined2 *)0x4562,0,0x1680,0);
  iVar6 = FUN_1000_5d8c(uVar13,400,0);
  *(int *)0x54aa = -iVar6;
  *(undefined2 *)0x9618 = 0;
  *(undefined2 *)0x961a = 3;
  *(undefined2 *)0xaf1c = 0x8000;
  *(undefined2 *)0xaf2c = 0x2800;
  *(undefined2 *)0x5496 = 0;
  *(undefined2 *)0x4568 = 0;
  *(undefined2 *)0x9336 = 0;
  *(undefined2 *)0x54ac = 0;
  *(undefined2 *)0x54ae = 0;
  *(undefined2 *)0x5494 = 30000;
  *(undefined2 *)0xb13c = 30000;
  *(undefined2 *)0x456e = 0;
  *(undefined2 *)0x4558 = 0;
  *(undefined2 *)0x456a = 0;
  bVar3 = true;
  bVar12 = false;
  bVar11 = false;
  *(undefined2 *)0x455a = 0;
  bVar5 = false;
  bVar4 = false;
  *(undefined2 *)0xaf2e = 0;
  *(undefined2 *)0xaf30 = 0;
  *(undefined2 *)0x1600 = 0;
  local_4 = 0;
  *(undefined2 *)0xaf38 = 0;
  do {
    if (*(uint *)0x1600 < local_4) {
      *(undefined2 *)0x1600 = 0;
      local_4 = 0;
    }
    iVar6 = *(int *)0x1600;
    if ((*(byte *)0xbdc & 0x80) != 0) {
      do {
      } while ((*(byte *)0xbdc & 0x80) != 0);
      while ((((((*(byte *)0xbd2 & 0x80) == 0 && ((*(byte *)0xbd3 & 0x80) == 0)) &&
               ((*(byte *)0xbd4 & 0x80) == 0)) &&
              (((*(byte *)0xbd5 & 0x80) == 0 && ((*(byte *)0xbd6 & 0x80) == 0)))) &&
             ((((*(byte *)0xbd7 & 0x80) == 0 &&
               (((*(byte *)0xbd8 & 0x80) == 0 && ((*(byte *)0xbd9 & 0x80) == 0)))) &&
              ((*(byte *)0xbda & 0x80) == 0))))) {
        if (((*(byte *)0xbdb & 0x80) != 0) || ((*(byte *)0xbdc & 0x80) != 0)) break;
      }
      if ((*(byte *)0xbda & 0x80) != 0) {
        return 7;
      }
      do {
        do {
        } while ((*(byte *)0xbd2 & 0x80) != 0);
      } while (((((((*(byte *)0xbd3 & 0x80) != 0) || ((*(byte *)0xbd4 & 0x80) != 0)) ||
                 ((*(byte *)0xbd5 & 0x80) != 0)) ||
                ((((*(byte *)0xbd6 & 0x80) != 0 || ((*(byte *)0xbd7 & 0x80) != 0)) ||
                 (((*(byte *)0xbd8 & 0x80) != 0 ||
                  (((*(byte *)0xbd9 & 0x80) != 0 || ((*(byte *)0xbda & 0x80) != 0)))))))) ||
               ((*(byte *)0xbdb & 0x80) != 0)) || ((*(byte *)0xbdc & 0x80) != 0));
      *(int *)0x1600 = iVar6;
    }
    if ((*(byte *)0xbda & 0x80) != 0) {
      return 7;
    }
    if (((*(int *)0x456a == 0) || (0x2a < *(uint *)0x456a)) &&
       (((*(int *)0x456e == 1 || (*(int *)0x456e == 2)) ||
        (((*(int *)0x456e == 3 && (*(int *)0x456a != 0)) || (0x6b < *(uint *)0x4558)))))) {
      return *(undefined2 *)0x456e;
    }
    FUN_1000_0c98(bVar12);
    FUN_1000_12f8();
    do {
    } while (*(int *)0x1600 == iVar6);
    FUN_1000_0ed0();
    if (*(int *)0x95f6 != 3) {
      FUN_1000_074c();
    }
    for (; local_4 < *(uint *)0x1600; local_4 = local_4 + 1) {
      if (*(int *)0x95f6 == 3) {
        FUN_1000_074c();
      }
      local_16 = FUN_1000_04c0(*(undefined2 *)0x9618,*(undefined2 *)0x961a,*(undefined2 *)0xaf1c);
      bVar10 = local_16 != 0;
      if (bVar3) {
        if (0x2800 < *(uint *)0xaf2c) {
          if (*(int *)0xaf2c == *(int *)((local_16 >> 8) * 2 + 0xe4)) {
            local_16 = local_16 >> 4;
          }
          else {
            local_16 = 0;
          }
        }
        FUN_1000_1b49(local_16);
        bVar11 = (local_16 & 0xf) == 8;
        bVar12 = (local_16 & 0xf) == 2;
      }
      else {
        bVar12 = false;
      }
      lVar14 = FUN_1000_5d80();
      uVar9 = (uint)((ulong)(lVar14 + -0x8000) >> 0x10);
      if (((uVar9 <= *(uint *)0x961a) &&
          ((uVar9 < *(uint *)0x961a || ((uint)(lVar14 + -0x8000) <= *(uint *)0x9618)))) &&
         ((iVar6 = FUN_1000_0533(*(undefined2 *)0x9618,*(undefined2 *)0x961a,*(undefined2 *)0xaf1c,
                                 *(undefined2 *)0xaf2c), iVar6 != 0 && (*(int *)0x456e == 0)))) {
        uVar7 = FUN_1000_0f05();
        return uVar7;
      }
      if (*(int *)0xaf2c != local_1e) {
        if ((*(int *)0x5496 == 0) || (1 < local_1a)) {
          if (*(int *)0x9336 < 1) {
            uVar9 = -*(int *)0x9336;
          }
          else {
            uVar9 = *(uint *)0x9336;
          }
          if (((uint)(((long)*(int *)0x4562 * 0x104 & 0xffffU) / 8) <= uVar9) &&
             (*(int *)0x456a == 0)) {
            if ((*(int *)0x456e == 0) &&
               ((*(int *)0x9336 < 0 && (iVar6 = FUN_1000_0476(), iVar6 == 0)))) {
              FUN_1000_03c2(1);
            }
            *(int *)0x9336 = (*(int *)0x9336 * -5) / 10;
            goto LAB_1000_24ba;
          }
        }
        *(undefined2 *)0x9336 = 0;
      }
LAB_1000_24ba:
      if (*(int *)0x456e == 0) {
        uVar13 = FUN_1000_5d4c(*(int *)0x9330,*(int *)0x9330 >> 0xf,0x4b,0);
        puVar1 = (uint *)0x54ac;
        uVar9 = *puVar1;
        *puVar1 = *puVar1 + (uint)uVar13;
        *(int *)0x54ae =
             *(int *)0x54ae + (int)((ulong)uVar13 >> 0x10) + (uint)CARRY2(uVar9,(uint)uVar13);
        if ((*(int *)0x54ae < 1) && (*(int *)0x54ae < 0)) {
          *(undefined2 *)0x54ac = 0;
          *(undefined2 *)0x54ae = 0;
        }
        else if ((-1 < *(int *)0x54ae) && ((0 < *(int *)0x54ae || (0x2aaa < *(uint *)0x54ac)))) {
          *(undefined2 *)0x54ac = 0x2aaa;
          *(undefined2 *)0x54ae = 0;
        }
        if ((!bVar11) &&
           (((!bVar4 && (bVar10)) ||
            ((*(int *)0x4568 == 0 &&
             ((0 < *(int *)0x9336 && ((uint)(*(int *)0xaf2c - local_c) < 0xf00)))))))) {
          *(int *)0x4568 = *(int *)0x95f4 * 0x1d;
        }
        if ((((!bVar4) && (bVar10)) && (*(int *)0x547a != 0)) && (*(uint *)0x4562 < 0x14)) {
          *(undefined2 *)0x9336 = 0x480;
          *(undefined2 *)0x5494 = *(undefined2 *)0x5494;
          bVar4 = true;
          local_c = *(int *)0xaf2c;
        }
      }
      if (((*(int *)0x4570 != 0) && (bVar4)) && ((!bVar5 && (0x36ff < *(uint *)0xaf2c)))) {
        FUN_1000_1dfa();
        bVar5 = true;
      }
      if (*(int *)0x456a == 0) {
        if (*(uint *)0xaf2c < 0x2800) {
          if (-0x6a < *(int *)0x9336) {
            *(undefined2 *)0x9336 = 0xff96;
          }
        }
        else {
          *(int *)0x9336 = *(int *)0x9336 + *(int *)0x54aa;
        }
      }
      else {
        if (*(int *)0x9336 < 0) {
          *(undefined2 *)0x9336 = 0;
        }
        if (*(int *)0x9336 < 0x47) {
          *(int *)0x9336 = *(int *)0x9336 + 0x27;
        }
        else {
          *(undefined2 *)0x9336 = 0x47;
        }
      }
      local_22 = *(uint *)0x54ac + *(uint *)0x9618;
      local_20 = *(int *)0x54ae + *(int *)0x961a + (uint)CARRY2(*(uint *)0x54ac,*(uint *)0x9618);
      iVar6 = *(int *)0x5496;
      if (bVar12 == false) {
        uVar9 = 0x618;
      }
      else {
        uVar9 = 0;
      }
      uVar13 = FUN_1000_5d4c(uVar9 + *(uint *)0x54ac,
                             *(int *)0x54ae + (uint)CARRY2(uVar9,*(uint *)0x54ac),*(int *)0x4568,
                             *(int *)0x4568 >> 0xf);
      iVar8 = FUN_1000_5e5a(uVar13,0x200,0);
      local_1c = iVar8 + *(int *)0xaf1c + iVar6;
      local_1e = *(int *)0x9336 + *(int *)0xaf2c;
      if (((*(uint *)0xaf1c < 0x2f80) && (0xd080 < local_1c)) ||
         ((local_1c < 0x2f80 && (0xd080 < *(uint *)0xaf1c)))) {
        local_1c = *(uint *)0xaf1c;
      }
      FUN_1000_186b(local_22,local_20,local_1c,local_1e);
      if ((((*(uint *)0x9618 != local_22) || (*(int *)0x961a != local_20)) &&
          (*(uint *)0xaf1c == local_1c)) &&
         (iVar6 = FUN_1000_1732(local_22,local_20,*(undefined2 *)0xaf1c,*(undefined2 *)0xaf2c),
         iVar6 != 0)) {
        iVar6 = FUN_1000_1732(local_22,local_20,*(int *)0xaf1c + -0x3a0,*(undefined2 *)0xaf2c);
        if (iVar6 == 0) {
          *(int *)0xaf1c = *(int *)0xaf1c + -0x3a0;
          local_22 = *(uint *)0x9618;
          local_20 = *(int *)0x961a;
          FUN_1000_03c2(2);
        }
        else {
          iVar6 = FUN_1000_1732(local_22,local_20,*(int *)0xaf1c + 0x3a0,*(undefined2 *)0xaf2c);
          if (iVar6 == 0) {
            *(int *)0xaf1c = *(int *)0xaf1c + 0x3a0;
            local_22 = *(uint *)0x9618;
            local_20 = *(int *)0x961a;
            FUN_1000_03c2(2);
          }
        }
      }
      if ((*(uint *)0x9618 != local_22) || (*(int *)0x961a != local_20)) {
        if (((*(int *)0x54ae < 0) || ((*(int *)0x54ae < 1 && (*(uint *)0x54ac < 0xe38)))) ||
           (*(int *)0x456a != 0)) {
          uVar9 = (local_20 - *(int *)0x54ae) - (uint)(local_22 < *(uint *)0x54ac);
          if ((uVar9 <= *(uint *)0x961a) &&
             ((uVar9 < *(uint *)0x961a || (local_22 - *(uint *)0x54ac < *(uint *)0x9618)))) {
            FUN_1000_03c2(2);
          }
        }
        else {
          *(undefined2 *)0x456a = 1;
          FUN_1000_03c2(0);
          if (*(int *)0x456e == 0) {
            *(undefined2 *)0x456e = 1;
          }
        }
        *(undefined2 *)0x54ac = 0;
        *(undefined2 *)0x54ae = 0;
      }
      if (*(uint *)0xaf1c != local_1c) {
        *(undefined2 *)0x4568 = 0;
        if (((0 < *(int *)0x5496) && (*(uint *)0xaf1c < local_1c)) ||
           ((*(int *)0x5496 < 0 && (local_1c < *(uint *)0xaf1c)))) {
          *(undefined2 *)0x5496 = 0;
        }
        puVar1 = (uint *)0x54ac;
        uVar9 = *puVar1;
        *puVar1 = *puVar1 - 0x97;
        *(int *)0x54ae = *(int *)0x54ae - (uint)(uVar9 < 0x97);
        if ((*(int *)0x54ae < 1) && (*(int *)0x54ae < 0)) {
          *(undefined2 *)0x54ac = 0;
          *(undefined2 *)0x54ae = 0;
        }
        else if ((-1 < *(int *)0x54ae) && ((0 < *(int *)0x54ae || (0x2aaa < *(uint *)0x54ac)))) {
          *(undefined2 *)0x54ac = 0x2aaa;
          *(undefined2 *)0x54ae = 0;
        }
      }
      bVar3 = false;
      if ((*(int *)0xaf2c != local_1e) && (*(int *)0x9336 < 0)) {
        *(undefined2 *)0x455a = 0;
        bVar5 = false;
        bVar4 = false;
        bVar3 = true;
        uVar2 = *(uint *)0xaf2e;
        iVar6 = *(int *)0xaf30;
        puVar1 = (uint *)0x54ac;
        uVar9 = *puVar1;
        *puVar1 = *puVar1 - uVar2;
        *(int *)0x54ae = (*(int *)0x54ae - iVar6) - (uint)(uVar9 < uVar2);
        if ((*(int *)0x54ae < 1) && (*(int *)0x54ae < 0)) {
          *(undefined2 *)0x54ac = 0;
          *(undefined2 *)0x54ae = 0;
        }
        else if ((-1 < *(int *)0x54ae) && ((0 < *(int *)0x54ae || (0x2aaa < *(uint *)0x54ac)))) {
          *(undefined2 *)0x54ac = 0x2aaa;
          *(undefined2 *)0x54ae = 0;
        }
        *(undefined2 *)0xaf2e = 0;
        *(undefined2 *)0xaf30 = 0;
        local_24 = 0;
        for (local_18 = 1; local_18 < 0xf; local_18 = local_18 + 1) {
          iVar6 = FUN_1000_1732(*(undefined2 *)0x9618,*(undefined2 *)0x961a,
                                local_18 * 0x80 + *(int *)0xaf1c,*(int *)0xaf2c + -1);
          if (iVar6 == 0) {
            local_24 = 1;
            local_1a = local_18;
            break;
          }
        }
        for (local_18 = 1; local_18 < 0xf; local_18 = local_18 + 1) {
          iVar6 = FUN_1000_1732(*(undefined2 *)0x9618,*(undefined2 *)0x961a,
                                *(int *)0xaf1c + local_18 * -0x80,*(int *)0xaf2c + -1);
          if (iVar6 == 0) {
            local_24 = local_24 + -1;
            local_1a = local_18;
            break;
          }
        }
        if (local_24 == 0) {
          *(undefined2 *)0x5496 = 0;
        }
        else {
          *(int *)0x5496 = *(int *)0x5496 + local_24 * 0x11;
        }
      }
      if (0x7fff < *(uint *)0xaf2c) {
        *(undefined2 *)0xaf2c = 0;
      }
      if (*(int *)0x456e == 0) {
        *(int *)0xb13c = *(int *)0xb13c - (int)(30000 / ((long)*(int *)0x4566 * 0x24 & 0xffffU));
        if (30000 < *(uint *)0xb13c) {
          *(undefined2 *)0xb13c = 0;
        }
        uVar13 = FUN_1000_5d4c((int)(30000 / (ulong)*(uint *)0x54a2),0,*(undefined2 *)0x54ac,
                               *(undefined2 *)0x54ae);
        iVar6 = FUN_1000_5e5a(uVar13,0,1);
        *(int *)0x5494 = *(int *)0x5494 - iVar6;
        if (30000 < *(uint *)0x5494) {
          *(undefined2 *)0x5494 = 0;
        }
      }
      if (*(int *)0x456e == 0) {
        if (*(uint *)0xaf2c < 0x2800) {
          *(undefined2 *)0x456e = 3;
        }
        if (*(int *)0x5494 == 0) {
          *(undefined2 *)0x456e = 4;
        }
        if (*(int *)0xb13c == 0) {
          *(undefined2 *)0x456e = 5;
        }
      }
      else {
        *(int *)0x4558 = *(int *)0x4558 + 1;
      }
      if (*(int *)0x456a != 0) {
        *(int *)0x456a = *(int *)0x456a + 1;
      }
    }
  } while( true );
}


// ---- FUN_1000_2b0f @ 1000:2b0f ----

undefined4 __cdecl16near FUN_1000_2b0f(undefined2 param_1,undefined2 param_2)

{
  undefined1 *puVar1;
  undefined1 *puVar2;
  int iVar3;
  undefined1 *puVar4;
  undefined1 *puVar5;
  
  out(0x3ce,5);
  out(0x3ce,0xf01);
  out(0x3ce,3);
  out(0x3ce,8);
  puVar4 = (undefined1 *)0x0;
  puVar5 = (undefined1 *)0x0;
  for (iVar3 = 8000; iVar3 != 0; iVar3 = iVar3 + -1) {
    puVar2 = puVar5;
    puVar5 = puVar5 + 1;
    puVar1 = puVar4;
    puVar4 = puVar4 + 1;
    *puVar2 = *puVar1;
  }
  return 0x3ce0008;
}


// ---- FUN_1000_2b3d @ 1000:2b3d ----

int __cdecl16near FUN_1000_2b3d(int param_1)

{
  int iVar1;
  int iVar2;
  int unaff_DS;
  
  *(int *)0xaf2a = unaff_DS + 0x31b;
  FUN_1000_3b9d();
  *(undefined2 *)0xaf1e = 0;
  *(undefined2 *)0x455c = 0;
  *(undefined2 *)0x960c = 0;
  *(undefined2 *)0x456c = 0;
  *(undefined2 *)0x41be = 0;
  *(undefined2 *)0xaf20 = 0xffff;
  *(undefined2 *)0x9334 = 0;
  if (*(int *)0x3c == 0) {
    FUN_1000_2b0f(0xa000,*(undefined2 *)0x5170);
    FUN_1000_2b0f(0xa200,*(undefined2 *)0x5170);
  }
  else {
    FUN_1000_6053(0xac80,0xa000,0xac80,*(undefined2 *)0x5170,0x4d80);
  }
  FUN_1000_1114(0x60,0x9c,(*(int *)0x4562 + -3) * 100,4);
  if (*(int *)0x3c == 0) {
    iVar1 = (uint)(*(int *)0x9334 == 0) * 0x200 + -0x6000;
  }
  else {
    iVar1 = *(int *)0x5478;
  }
  iVar1 = FUN_1000_0baf(0,0x2800,1,0,iVar1);
  iVar2 = FUN_1000_0be9(0x8000);
  FUN_1000_2d1f(0x100,0x18,0x50,*(int *)0xaf34 + ((iVar2 * 3 + iVar1) * 3 + 0xe) * 0x2d0,
                *(undefined2 *)0xaf36);
  FUN_1000_4b8e(0x41c2,1,0x24);
  iVar1 = FUN_1000_1fd9();
  if (*(int *)0x9334 != 0) {
    *(undefined2 *)0x9334 = 0;
    FUN_1000_0ed0();
  }
  if (iVar1 == 0) {
    FUN_1000_3c9a();
    if (param_1 == 0) {
      FUN_1000_4526(0x68,0x50,0xd42,99);
    }
    else {
      FUN_1000_4526(0x84,0x50,0xd3a,99);
    }
    FUN_1000_4459(0x1b);
  }
  FUN_1000_4b8e(0x41c2,0,0x24);
  FUN_1000_3c03();
  return iVar1;
}


// ---- FUN_1000_2cce @ 1000:2cce ----

undefined2 __cdecl16near FUN_1000_2cce(void)

{
  undefined2 uVar1;
  undefined2 unaff_DS;
  
  uVar1 = FUN_1000_3a96();
  *(undefined2 *)0xe38 = 0x34a7;
  *(undefined2 *)0xe3a = 0x3153;
  *(undefined2 *)0xe3c = 0x3190;
  *(undefined2 *)0xe3e = 0x325b;
  if (*(int *)0x3c != 1) {
    *(undefined2 *)0xe38 = 0x347e;
    *(undefined2 *)0xe3a = 0x309f;
    *(undefined2 *)0xe3c = 0x30f5;
    *(undefined2 *)0xe3e = 0x31db;
    FUN_1000_3a3f();
    out(0x3ce,5);
    out(0x3ce,0xf01);
    uVar1 = 3;
    out(0x3ce,3);
  }
  return uVar1;
}


// ---- FUN_1000_2d1f @ 1000:2d1f ----

void __cdecl16near
FUN_1000_2d1f(undefined2 param_1,undefined2 param_2,undefined2 param_3,undefined2 param_4,
             undefined2 param_5,undefined2 param_6,undefined2 param_7,undefined2 param_8)

{
  int *piVar1;
  undefined2 *puVar2;
  undefined2 *puVar3;
  int iVar4;
  int iVar5;
  undefined2 *puVar6;
  undefined2 *puVar7;
  undefined2 unaff_SS;
  undefined2 unaff_DS;
  undefined1 *puVar8;
  
  puVar8 = &stack0xfffe;
  *(undefined2 *)0xe28 = param_1;
  *(undefined2 *)0xe2a = param_2;
  *(undefined2 *)0xe2c = param_3;
  *(undefined2 *)0xe2e = param_4;
  *(undefined2 *)0xe30 = param_5;
  *(undefined2 *)0xe32 = param_6;
  *(undefined2 *)0xe34 = param_7;
  *(undefined2 *)0xe36 = param_8;
  (*(code *)*(undefined2 *)0xe38)();
  iVar4 = (*(uint *)0xe2a >> 3) * 0xe + 0x168e;
  *(undefined2 *)0xe4a = 0;
  *(undefined2 *)0xe44 = 0xb;
  do {
    while( true ) {
      *(undefined2 *)0xe48 = 0;
      *(undefined2 *)0xe40 = *(undefined2 *)0xe3a;
      do {
        *(undefined2 *)0xe46 = 4;
        do {
          (*(code *)*(undefined2 *)((*(byte *)(iVar4 + 1) & 0xf) * 2 + 0xbaf))(puVar8);
          iVar5 = iVar4 + 2;
          if (*(int *)0xe48 != 0) {
            iVar5 = iVar4 + -2;
          }
          piVar1 = (int *)0xe46;
          *piVar1 = *piVar1 + -1;
          iVar4 = iVar5;
        } while (*piVar1 != 0);
        iVar4 = iVar5 + 4;
        *(undefined2 *)0xe40 = *(undefined2 *)0xe3c;
        *(int *)0xe48 = *(int *)0xe48 + 1;
      } while (*(uint *)0xe48 < 2);
      if ((*(int *)0xe44 != 4) || (*(int *)0xe4a = *(int *)0xe4a + 1, 1 < *(uint *)0xe4a)) break;
      iVar4 = iVar5 + -4;
      puVar8 = (undefined1 *)0x2e2a;
      (*(code *)*(undefined2 *)0xe3e)();
    }
    iVar4 = iVar5 + -0x12;
    piVar1 = (int *)0xe44;
    *piVar1 = *piVar1 + -1;
  } while (*piVar1 != 0);
  FUN_1000_34ae();
  *(undefined2 *)0xe6a = *(undefined2 *)0xe2a;
  *(undefined2 *)0xe6e = *(undefined2 *)0xe6c;
  *(undefined2 *)0xe72 = *(undefined2 *)0xe70;
  puVar6 = (undefined2 *)0xe86;
  puVar7 = (undefined2 *)0x1243;
  for (iVar4 = 0x1de; iVar4 != 0; iVar4 = iVar4 + -1) {
    puVar3 = puVar7;
    puVar7 = puVar7 + 1;
    puVar2 = puVar6;
    puVar6 = puVar6 + 1;
    *puVar3 = *puVar2;
  }
  return;
}


// ---- FUN_1000_34ae @ 1000:34ae ----

void __cdecl16near FUN_1000_34ae(void)

{
  uint *puVar1;
  undefined2 *puVar2;
  undefined2 *puVar3;
  undefined2 uVar4;
  undefined2 uVar5;
  int in_AX;
  int iVar6;
  byte *pbVar7;
  undefined2 *puVar8;
  undefined2 *puVar9;
  undefined2 unaff_SS;
  
  if (*(int *)0x3c == 0) {
    return;
  }
  *(undefined2 *)0xe66 = *(undefined2 *)0x5170;
  *(undefined2 *)0xe68 = *(undefined2 *)0xe36;
  *(undefined2 *)0xe42 = 0x364f;
  if (in_AX != 0) {
    *(undefined2 *)0xe66 = *(undefined2 *)0xe36;
    *(undefined2 *)0xe68 = 0xa000;
    *(undefined2 *)0xe42 = 0x36f3;
  }
  if (*(int *)0xe32 == 0) {
    if (*(int *)0xe2a == *(int *)0xe6a) goto LAB_1000_3627;
    if ((uint)(*(int *)0xe2a - *(int *)0xe6a) < 8) {
      *(undefined2 *)0xe64 = 0;
      if (*(uint *)0xe2a >> 3 == *(uint *)0xe6a >> 3) {
        *(int *)0xe64 = *(int *)0xe64 + 0x30;
      }
      *(undefined2 *)0xe62 = *(undefined2 *)((*(uint *)0xe6a & 7) * 2 + 0xe76);
      *(undefined2 *)0xe60 = *(undefined2 *)((*(uint *)0xe2a & 7) * 2 + 0xe76);
      *(int *)0xe4c = (*(uint *)0xe2a >> 3) * 0xe + 0x168e;
      *(undefined2 *)0xe44 = 0xb;
      do {
        *(undefined2 *)0xe46 = 1;
        do {
          *(undefined2 *)0xe48 = 0;
          do {
            iVar6 = -*(int *)0xe46 + 4;
            if (*(int *)0xe48 == 1) {
              iVar6 = -(-*(int *)0xe46 + -2);
            }
            pbVar7 = (byte *)(*(int *)0xe4c + iVar6 * 2);
            *(uint *)0xe56 = *pbVar7 & 0xf;
            *(uint *)0xe5c = (uint)(*pbVar7 >> 4);
            *(uint *)0xe4e = (uint)*(byte *)((pbVar7[1] & 7) + 0xba7);
            *(uint *)0xe58 = pbVar7[-0xe] & 0xf;
            *(uint *)0xe5e = (uint)(pbVar7[-0xe] >> 4);
            *(uint *)0xe50 = (uint)*(byte *)((pbVar7[-0xd] & 7) + 0xba7);
            iVar6 = *(int *)0xe48 * -4;
            *(uint *)0xe5a = pbVar7[iVar6 + 2] & 0xf;
            *(uint *)0xe52 = (uint)*(byte *)((pbVar7[iVar6 + 3] & 7) + 0xba7);
            *(uint *)0xe54 = (uint)*(byte *)((pbVar7[iVar6 + -0xb] & 7) + 0xba7);
            (*(code *)*(undefined2 *)0xe42)();
            puVar1 = (uint *)0xe48;
            *puVar1 = *puVar1 ^ 1;
          } while (*puVar1 != 0);
          *(int *)0xe46 = *(int *)0xe46 + 1;
        } while (*(uint *)0xe46 < 5);
        *(int *)0xe4c = *(int *)0xe4c + -0xe;
        *(int *)0xe44 = *(int *)0xe44 + -1;
      } while (*(int *)0xe44 != 1);
      goto LAB_1000_3627;
    }
  }
  puVar8 = (undefined2 *)0x2800;
  iVar6 = 0x4240;
  if (*(int *)0xe32 != 0) {
    puVar8 = (undefined2 *)0x0;
    iVar6 = 0x5640;
  }
  uVar4 = *(undefined2 *)0xe66;
  uVar5 = *(undefined2 *)0xe68;
  puVar9 = puVar8;
  for (; iVar6 != 0; iVar6 = iVar6 + -1) {
    puVar3 = puVar9;
    puVar9 = puVar9 + 1;
    puVar2 = puVar8;
    puVar8 = puVar8 + 1;
    *puVar3 = *puVar2;
  }
LAB_1000_3627:
  FUN_1000_39d4();
  return;
}


// ---- FUN_1000_39d4 @ 1000:39d4 ----

void __cdecl16near FUN_1000_39d4(void)

{
  undefined2 unaff_SS;
  
  FUN_1000_3a22();
  FUN_1000_3a22();
  if (*(int *)0xe68 == -0x6000) {
    FUN_1000_3a22();
    FUN_1000_3a22();
  }
  return;
}


// ---- FUN_1000_3a22 @ 1000:3a22 ----

void __cdecl16near FUN_1000_3a22(void)

{
  undefined1 *puVar1;
  int iVar2;
  int in_DX;
  char *in_BX;
  undefined1 *unaff_SI;
  undefined1 *puVar3;
  undefined2 unaff_ES;
  undefined2 unaff_SS;
  undefined2 unaff_DS;
  
  do {
    iVar2 = 0x1d;
    puVar1 = unaff_SI;
    do {
      puVar3 = puVar1;
      if (*in_BX == '\x02') {
        *unaff_SI = *puVar3;
      }
      unaff_SI = unaff_SI + 1;
      in_BX = in_BX + 1;
      iVar2 = iVar2 + -1;
      puVar1 = puVar3 + 1;
    } while (iVar2 != 0);
    unaff_SI = puVar3 + 0x124;
    in_DX = in_DX + -1;
  } while (in_DX != 0);
  return;
}


// ---- FUN_1000_3a3f @ 1000:3a3f ----

void __cdecl16near FUN_1000_3a3f(void)

{
  byte bVar1;
  undefined2 uVar2;
  byte bVar3;
  int iVar4;
  byte bVar5;
  byte *pbVar6;
  byte *pbVar7;
  byte *pbVar8;
  int iVar9;
  undefined2 unaff_SS;
  
  iVar9 = 0;
  do {
    uVar2 = *(undefined2 *)(iVar9 + 0xe76);
    iVar4 = 0x410;
    pbVar6 = (byte *)0x270;
    do {
      *(uint *)(pbVar6 + 1) = *(uint *)(pbVar6 + 1) >> 3;
      pbVar8 = pbVar6;
      while( true ) {
        pbVar7 = pbVar8 + 3;
        pbVar6 = pbVar8 + 4;
        bVar1 = *pbVar7;
        if (bVar1 == 0xff) break;
        bVar5 = ~(-1 << (bVar1 & 7));
        bVar3 = *pbVar6 - (bVar1 & 7);
        if (*pbVar6 < (bVar1 & 7)) {
          bVar5 = bVar5 & -1 << (-bVar3 & 0x1f);
          bVar3 = 0;
        }
        *(uint *)pbVar7 = CONCAT11(bVar5,(bVar1 >> 3) + 1);
        pbVar8[5] = bVar3;
        pbVar8 = pbVar7;
      }
      iVar4 = iVar4 + -1;
    } while (iVar4 != 0);
    iVar9 = iVar9 + 2;
  } while (iVar9 != 0x10);
  return;
}


// ---- FUN_1000_3a96 @ 1000:3a96 ----

void __cdecl16near FUN_1000_3a96(void)

{
  char cVar1;
  char *pcVar2;
  char *pcVar3;
  undefined2 uVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  char *pcVar8;
  char *pcVar9;
  char *pcVar10;
  char *pcVar11;
  undefined2 unaff_SS;
  
  iVar7 = 0;
  do {
    uVar4 = *(undefined2 *)(iVar7 + 0xe76);
    iVar6 = 0x410;
    pcVar10 = (char *)0x0;
    pcVar8 = (char *)*(undefined2 *)0x0;
    for (iVar5 = 0x138; iVar5 != 0; iVar5 = iVar5 + -1) {
      pcVar3 = pcVar10;
      pcVar10 = pcVar10 + 2;
      pcVar2 = pcVar8;
      pcVar8 = pcVar8 + 2;
      *(undefined2 *)pcVar3 = *(undefined2 *)pcVar2;
    }
    do {
      *pcVar10 = *pcVar8;
      pcVar9 = pcVar8 + 3;
      *(undefined2 *)(pcVar10 + 1) = *(undefined2 *)(pcVar8 + 1);
      pcVar11 = pcVar10;
      while( true ) {
        pcVar8 = pcVar9 + 1;
        cVar1 = *pcVar9;
        pcVar10 = pcVar11 + 4;
        pcVar11[3] = cVar1;
        if (cVar1 == -1) break;
        pcVar9 = pcVar9 + 2;
        *pcVar10 = *pcVar8;
        pcVar11[5] = '\0';
        pcVar11 = pcVar11 + 3;
      }
      iVar6 = iVar6 + -1;
    } while (iVar6 != 0);
    iVar7 = iVar7 + 2;
  } while (iVar7 != 0x10);
  return;
}


// ---- FUN_1000_3acc @ 1000:3acc ----

uint __cdecl16near FUN_1000_3acc(void)

{
  uint uVar1;
  
  uVar1 = uRam00000020;
  DAT_1000_3b67 = uRam00000020;
  DAT_1000_3b69 = uRam00000022;
  uRam00000020 = 0x3b17;
  uRam00000022 = 0x1000;
  uRam00000090 = 0x3b14;
  uRam00000092 = 0x1000;
  out(0x43,0x36);
  out(0x40,0xe4);
  out(0x40,0x19);
  out(0x43,0xb6);
  out(0x42,2);
  out(0x42,0);
  return uVar1 & 0xff00;
}


// ---- FUN_1000_3b6b @ 1000:3b6b ----

uint __cdecl16near FUN_1000_3b6b(void)

{
  undefined1 uVar1;
  uint uVar2;
  
  uRam00000020 = DAT_1000_3b67;
  uRam00000022 = DAT_1000_3b69;
  out(0x43,0x36);
  out(0x40,0);
  out(0x40,0);
  out(0x43,0xb6);
  out(0x42,0);
  out(0x42,0);
  uVar1 = in(0x61);
  uVar2 = CONCAT11((char)((uint)DAT_1000_3b67 >> 8),uVar1) & 0xfffc;
  out(0x61,(char)uVar2);
  return uVar2;
}


// ---- FUN_1000_3b9d @ 1000:3b9d ----

void __cdecl16near FUN_1000_3b9d(void)

{
  byte *pbVar1;
  int iVar2;
  undefined2 unaff_DS;
  
  iVar2 = -1;
  do {
    pbVar1 = (byte *)(iVar2 + 0xbd3);
    *pbVar1 = *pbVar1 & 0x7f;
    iVar2 = iVar2 + 1;
  } while (*pbVar1 != 0);
  DAT_1000_3bff = uRam00000024;
  DAT_1000_3c01 = uRam00000026;
  uRam00000024 = 0x3bcc;
  uRam00000026 = 0x1000;
  return;
}


// ---- FUN_1000_3c03 @ 1000:3c03 ----

void __cdecl16near FUN_1000_3c03(void)

{
  uRam00000024 = DAT_1000_3bff;
  uRam00000026 = DAT_1000_3c01;
  return;
}


// ---- FUN_1000_3c52 @ 1000:3c52 ----

void __cdecl16near FUN_1000_3c52(int param_1,int param_2,int param_3,undefined1 param_4)

{
  byte *pbVar1;
  undefined2 uVar2;
  byte bVar3;
  undefined1 *puVar4;
  int iVar5;
  char cVar6;
  byte *pbVar7;
  undefined1 *puVar8;
  undefined2 unaff_DS;
  bool bVar9;
  
  pbVar7 = (byte *)(param_3 * 8 + *(int *)0x3184);
  uVar2 = *(undefined2 *)0x3186;
  puVar4 = (undefined1 *)(param_2 * 0x140 + param_1);
  cVar6 = '\b';
  do {
    pbVar1 = pbVar7;
    pbVar7 = pbVar7 + 1;
    bVar3 = *pbVar1;
    iVar5 = 8;
    do {
      puVar8 = puVar4;
      bVar9 = (char)bVar3 < '\0';
      bVar3 = bVar3 << 1 | bVar9;
      if (bVar9) {
        *puVar8 = param_4;
      }
      iVar5 = iVar5 + -1;
      puVar4 = puVar8 + 1;
    } while (iVar5 != 0);
    puVar4 = puVar8 + 0x139;
    cVar6 = cVar6 + -1;
  } while (cVar6 != '\0');
  return;
}


// ---- FUN_1000_3c9a @ 1000:3c9a ----

void __cdecl16near FUN_1000_3c9a(void)

{
  undefined2 unaff_DS;
  
  if (*(char *)0x3c == '\0') {
    out(0x3ce,0x205);
    out(0x3ce,0xf01);
    out(0x3ce,3);
  }
  return;
}


// ---- FUN_1000_3cb1 @ 1000:3cb1 ----

void __cdecl16near
FUN_1000_3cb1(undefined2 param_1,uint param_2,int param_3,int param_4,undefined2 param_5)

{
  undefined2 uVar1;
  byte bVar2;
  int iVar3;
  undefined1 *puVar4;
  undefined1 *puVar5;
  undefined1 *puVar6;
  undefined1 *puVar7;
  bool bVar8;
  
  puVar6 = (undefined1 *)(param_2 >> 3 | param_3 << 0xd);
  puVar4 = (undefined1 *)0x0;
                    /* WARNING: Read-only address (ram,0x00013cf5) is written */
  uRam00013cf5 = param_5;
  iRam00013d00 = param_4 + -1;
                    /* WARNING: Read-only address (ram,0x00013d00) is written */
  uVar1 = CONCAT11(0x80 >> ((byte)param_2 & 7),8);
  while( true ) {
    out(0x3ce,uVar1);
    iVar3 = 0x4444;
    puVar5 = puVar4;
    puVar7 = puVar6;
    do {
      *puVar7 = *puVar5;
      puVar7 = puVar7 + 0x28;
      puVar5 = puVar5 + 0x4445;
      iVar3 = iVar3 + -1;
    } while (iVar3 != 0);
    param_4 = param_4 + -1;
    if (param_4 == 0) break;
    puVar4 = puVar4 + 1;
    bVar2 = (byte)((uint)uVar1 >> 8);
    bVar8 = (bool)(bVar2 & 1);
    uVar1 = CONCAT11(bVar2 >> 1 | bVar8 << 7,(char)uVar1);
    if (bVar8) {
      puVar6 = puVar6 + 1;
    }
  }
  return;
}


// ---- FUN_1000_3d18 @ 1000:3d18 ----

void __cdecl16near FUN_1000_3d18(byte *param_1,undefined2 param_2)

{
  byte *pbVar1;
  undefined2 uVar2;
  undefined2 uVar3;
  byte bVar4;
  int iVar5;
  int iVar6;
  byte *pbVar7;
  byte *pbVar8;
  byte *pbVar9;
  byte *pbVar10;
  byte *pbVar11;
  undefined2 unaff_SS;
  undefined2 unaff_DS;
  undefined2 uVar12;
  bool bVar13;
  byte bVar14;
  
  uVar2 = *(undefined2 *)0x961c;
  pbVar10 = (byte *)((uint)param_1 >> 3);
                    /* WARNING: Read-only address (ram,0x00013d73) is written */
  uRam00013d73 = param_2;
  iRam00013d8b = *(int *)0x9612 + -1;
                    /* WARNING: Read-only address (ram,0x00013d8b) is written */
  uRam00013d7e = *(undefined1 *)0xaf3a;
                    /* WARNING: Read-only address (ram,0x00013d7e) is written */
  uRam00013d7a = *(undefined1 *)0x9614;
                    /* WARNING: Read-only address (ram,0x00013d7a) is written */
  uVar3 = CONCAT11(0x80 >> ((byte)param_1 & 7),8);
  iVar6 = *(int *)0x9612;
  pbVar8 = (byte *)0x0;
  uVar12 = *(undefined2 *)0x4514;
  do {
    out(0x3ce,uVar3);
    iVar5 = 0x4444;
    pbVar7 = param_1;
    pbVar9 = pbVar8;
    pbVar11 = pbVar10;
    do {
      bVar4 = *pbVar9;
      bVar13 = bVar4 < 0x11;
      if (!bVar13) {
        if (bVar4 < 0x11) {
          bVar4 = *pbVar7;
          uVar12 = *(undefined2 *)0x4514;
        }
        bVar13 = false;
        pbVar1 = pbVar11;
        pbVar11 = pbVar11 + 1;
        *pbVar1 = bVar4;
      }
      pbVar11 = pbVar11 + bVar13 + 0x27;
      pbVar7 = pbVar7 + 0x140;
      pbVar9 = pbVar9 + 0x4445;
      iVar5 = iVar5 + -1;
    } while (iVar5 != 0);
    param_1 = param_1 + 1;
    pbVar8 = pbVar8 + 1;
    bVar4 = (byte)((uint)uVar3 >> 8);
    bVar14 = bVar4 & 1;
    uVar3 = CONCAT11(bVar4 >> 1 | bVar14 << 7,(char)uVar3);
    pbVar10 = pbVar10 + bVar14;
    iVar6 = iVar6 + -1;
  } while (iVar6 != 0);
  return;
}


// ---- FUN_1000_3d9e @ 1000:3d9e ----

void __cdecl16near FUN_1000_3d9e(undefined2 param_1,int param_2,uint param_3,uint param_4)

{
  undefined2 uVar1;
  uint *puVar2;
  char cVar4;
  uint uVar3;
  uint uVar5;
  char cVar6;
  uint *puVar7;
  undefined2 unaff_SS;
  
  puVar7 = (uint *)0x0;
  do {
    puVar2 = puVar7;
    for (uVar5 = param_3 >> 1; uVar5 != 0; uVar5 = uVar5 - 1) {
      uVar3 = *(uint *)((*puVar2 & 0xff) * 2 + -0x50c4);
      uVar1 = *(undefined2 *)((*puVar2 >> 8) * 2 + -0x50c4);
      cVar6 = (char)uVar3;
      cVar4 = (char)(uVar3 >> 8);
      if (param_4 == 0) {
        uVar3 = CONCAT11(cVar6,cVar4);
      }
      if (cVar6 == cVar4) {
        uVar3 = CONCAT11((char)(uVar3 >> 8),cVar6);
      }
      cVar6 = (char)uVar1;
      if (cVar6 == (char)((uint)uVar1 >> 8)) {
        uVar3 = CONCAT11(cVar6,(char)uVar3);
      }
      *puVar2 = uVar3;
      puVar2 = puVar2 + 1;
    }
    puVar7 = puVar2;
    if ((param_3 & 1) != 0) {
      puVar7 = (uint *)((int)puVar2 + 1);
      uVar5 = *(uint *)((uint)(byte)*puVar2 * 2 + -0x50c4);
      if (param_4 == 0) {
        uVar5 = uVar5 >> 8;
      }
      *(byte *)puVar2 = (byte)uVar5;
    }
    param_4 = param_4 ^ 1;
    param_2 = param_2 + -1;
  } while (param_2 != 0);
  return;
}


// ---- FUN_1000_3e0f @ 1000:3e0f ----

void __cdecl16near FUN_1000_3e0f(uint param_1,byte param_2,int param_3)

{
  undefined1 *puVar1;
  undefined1 *puVar2;
  
  out(0x3ce,5);
  out(0x3ce,param_3 << 8);
  puVar2 = (undefined1 *)((uint)param_2 * 0x28 + (param_1 >> 3));
  out(0x3ce,CONCAT11(0x80 >> ((byte)param_1 & 7),8));
  puVar1 = puVar2;
  *puVar1 = *puVar1;
  puVar1 = puVar2 + 0x2000;
  *puVar1 = *puVar1;
  return;
}


// ---- FUN_1000_3e4c @ 1000:3e4c ----

undefined4 __cdecl16near FUN_1000_3e4c(uint param_1,byte param_2)

{
  byte bVar1;
  undefined2 uVar2;
  char cVar3;
  byte bVar4;
  uint uVar5;
  byte bVar6;
  bool bVar7;
  
  bVar7 = false;
  uVar5 = (uint)(byte)(((byte)param_1 & 7) + 1);
  out(0x3ce,0xff08);
  uVar2 = 0x304;
  do {
    out(0x3ce,uVar2);
    bVar6 = *(byte *)((uint)param_2 * 0x28 + (param_1 >> 3));
    bVar4 = (byte)uVar5;
    bVar1 = bVar4 == 0 & bVar7;
    bVar7 = (int)uVar5 < 0;
    bVar6 = (char)(uVar5 >> 8) << 1 |
            bVar1 | (bVar4 != 0 && ((bVar6 << (bVar4 & 7) | bVar6 >> 8 - (bVar4 & 7)) & 1) != 0);
    uVar5 = CONCAT11(bVar6,bVar4);
    cVar3 = (char)((uint)uVar2 >> 8) + -1;
    uVar2 = CONCAT11(cVar3,(char)uVar2);
  } while (-1 < cVar3);
  return CONCAT22(0x3ce,(uint)bVar6);
}


// ---- FUN_1000_3e8a @ 1000:3e8a ----

void __cdecl16near FUN_1000_3e8a(uint param_1,uint param_2,int param_3,int param_4)

{
  byte *pbVar1;
  byte bVar2;
  undefined4 uVar3;
  int iVar4;
  byte *pbVar5;
  byte *pbVar6;
  undefined2 unaff_DS;
  
  out(0x3ce,param_4 << 8);
  out(0x3ce,5);
  uVar3 = *(undefined4 *)0x3184;
  pbVar5 = (byte *)((int)uVar3 + param_3 * 8);
  pbVar6 = (byte *)((param_2 & 0xff) * 0x28 + (param_1 >> 3));
  cRam00013eda = -(((byte)param_1 & 7) - 8);
                    /* WARNING: Read-only address (ram,0x00013eda) is written */
  iVar4 = 8;
  do {
    pbVar1 = pbVar5;
    pbVar5 = pbVar5 + 1;
    bVar2 = *pbVar1;
    out(0x3ce,CONCAT11((char)(((uint)bVar2 << 7) >> 8),8));
    *pbVar6 = *pbVar6 | 8;
    out(0x3ce,CONCAT11((char)((uint)bVar2 << 7),8));
    pbVar6[1] = pbVar6[1] | 8;
    pbVar6 = pbVar6 + 0x28;
    iVar4 = iVar4 + -1;
  } while (iVar4 != 0);
  return;
}


// ---- FUN_1000_3ef4 @ 1000:3ef4 ----

undefined2 __cdecl16near FUN_1000_3ef4(undefined2 param_1,undefined2 param_2)

{
  undefined2 uVar1;
  undefined2 unaff_DS;
  
  uVar1 = FUN_1000_5c36(param_1,param_2);
  *(undefined2 *)(*(int *)0x4564 * 2 + -0x6cc8) = uVar1;
  *(int *)0x4564 = *(int *)0x4564 + 1;
  return uVar1;
}


// ---- FUN_1000_3f20 @ 1000:3f20 ----

void __cdecl16near FUN_1000_3f20(void)

{
  undefined2 unaff_DS;
  
  *(undefined2 *)(*(int *)0x4564 * 2 + -0x6cc8) = 1;
  *(int *)0x4564 = *(int *)0x4564 + 1;
  return;
}


// ---- FUN_1000_3f3b @ 1000:3f3b ----

void __cdecl16near FUN_1000_3f3b(void)

{
  undefined2 unaff_DS;
  
  *(int *)0x4564 = *(int *)0x4564 + -1;
  while (*(int *)(*(int *)0x4564 * 2 + -0x6cc8) != 1) {
    FUN_1000_609f(*(undefined2 *)(*(int *)0x4564 * 2 + -0x6cc8));
    *(int *)0x4564 = *(int *)0x4564 + -1;
  }
  return;
}


// ---- FUN_1000_3f72 @ 1000:3f72 ----

void __cdecl16near FUN_1000_3f72(void)

{
  undefined2 unaff_DS;
  
  *(int *)0x4564 = *(int *)0x4564 + -1;
  FUN_1000_609f(*(undefined2 *)(*(int *)0x4564 * 2 + -0x6cc8));
  return;
}


// ---- FUN_1000_3f91 @ 1000:3f91 ----

undefined2 __cdecl16near FUN_1000_3f91(int param_1,int param_2)

{
  undefined2 uVar1;
  undefined2 unaff_DS;
  
  FUN_1000_6576();
  FUN_1000_6576();
  uVar1 = FUN_1000_6490();
  if (*(int *)0x41aa == 0) {
    FUN_1000_6595(param_1 + param_2 * 3);
  }
  FUN_1000_6595(0xaf3c);
  return uVar1;
}


// ---- FUN_1000_3fe2 @ 1000:3fe2 ----

undefined2 __cdecl16near FUN_1000_3fe2(undefined2 *param_1,undefined2 param_2)

{
  undefined2 uVar1;
  undefined2 unaff_DS;
  
  FUN_1000_6576();
  FUN_1000_6576();
  param_1[1] = param_2;
  uVar1 = FUN_1000_6490();
  param_1[2] = uVar1;
  uVar1 = FUN_1000_3ef4(param_1[2] * 3,0);
  *param_1 = uVar1;
  if (*(int *)0x41aa == 0) {
    FUN_1000_6595(0,uVar1,param_1[2] * 3);
    FUN_1000_6595(0xaf3c);
  }
  return param_1[2];
}


// ---- FUN_1000_4052 @ 1000:4052 ----

void __cdecl16near FUN_1000_4052(char *param_1,int param_2,int param_3,char param_4)

{
  char *pcVar1;
  int iVar2;
  
  iVar2 = (int)((ulong)param_1 >> 0x10);
  pcVar1 = (char *)param_1;
  do {
    do {
      if (*pcVar1 != '\0') {
        *pcVar1 = *pcVar1 + param_4;
      }
      pcVar1 = pcVar1 + 1;
      if (pcVar1 == (char *)0x0) {
        iVar2 = iVar2 + 0x1000;
      }
      param_2 = param_2 + -1;
    } while (param_2 != 0);
    param_3 = param_3 + -1;
  } while (-1 < param_3);
  return;
}


// ---- FUN_1000_4084 @ 1000:4084 ----

void __cdecl16near FUN_1000_4084(undefined2 *param_1,undefined2 param_2)

{
  int iVar1;
  undefined2 uVar2;
  undefined2 unaff_DS;
  
  FUN_1000_6576();
  FUN_1000_6595(param_1);
  iVar1 = param_1[2] * param_1[3];
  uVar2 = FUN_1000_3ef4(iVar1,0);
  *param_1 = uVar2;
  FUN_1000_0069();
  FUN_1000_66e6(0,uVar2,iVar1);
  if (*(int *)0x3c == 0) {
    FUN_1000_3d9e(*param_1,param_1[2],param_1[3],param_1[1] & 1 ^ (uint)param_1[1] / 0x140 & 1);
  }
  else {
    FUN_1000_4052(0,uVar2,iVar1,0,param_2);
  }
  return;
}


// ---- FUN_1000_411b @ 1000:411b ----

void __cdecl16near FUN_1000_411b(undefined2 param_1)

{
  undefined2 uVar1;
  
  uVar1 = FUN_1000_5c77(param_1,0,0x1000,0);
  FUN_1000_6420(uVar1);
  return;
}


// ---- FUN_1000_413c @ 1000:413c ----

void __cdecl16near FUN_1000_413c(void)

{
  undefined2 unaff_DS;
  
  FUN_1000_5c59(*(undefined2 *)0x41ac);
  FUN_1000_0069();
  return;
}


// ---- FUN_1000_4153 @ 1000:4153 ----

void __cdecl16near FUN_1000_4153(void)

{
  int iVar1;
  undefined2 unaff_DS;
  
  while (iVar1 = FUN_1000_5fcc(), iVar1 != 0) {
    FUN_1000_5feb();
    if (*(int *)0xaf32 != 0) {
      *(undefined2 *)0x54a0 = 1;
    }
  }
  return;
}


// ---- FUN_1000_417e @ 1000:417e ----

void __cdecl16near
FUN_1000_417e(undefined2 param_1,undefined2 param_2,undefined1 param_3,undefined1 param_4)

{
  undefined2 unaff_DS;
  
  *(undefined2 *)0x4512 = param_1;
  *(undefined2 *)0x961c = param_2;
  *(undefined1 *)0xaf3a = param_3;
  *(undefined1 *)0x9614 = param_4;
  return;
}


// ---- FUN_1000_41a0 @ 1000:41a0 ----

void __cdecl16near FUN_1000_41a0(byte *param_1,byte *param_2,int param_3,int param_4)

{
  byte *pbVar1;
  byte *pbVar2;
  byte bVar3;
  undefined2 uVar4;
  undefined2 uVar5;
  undefined2 uVar6;
  byte bVar7;
  int iVar8;
  byte *pbVar9;
  byte *pbVar10;
  undefined2 unaff_SS;
  undefined2 unaff_DS;
  
  uRam000141e9 = *(undefined1 *)0x9614;
                    /* WARNING: Read-only address (ram,0x000141e9) is written */
  bVar3 = *(byte *)0xaf3a;
  uVar4 = *(undefined2 *)0x4512;
  uVar5 = *(undefined2 *)0x4514;
  uVar6 = *(undefined2 *)0x961c;
  pbVar9 = param_1;
  for (iVar8 = param_3; iVar8 != 0; iVar8 = iVar8 + -1) {
    pbVar2 = pbVar9;
    pbVar9 = pbVar9 + 1;
    pbVar1 = param_1;
    param_1 = param_1 + 1;
    *pbVar2 = *pbVar1;
  }
  iVar8 = (*(int *)0x9612 - param_3) - param_4;
  do {
    pbVar1 = param_2;
    param_2 = param_2 + 1;
    bVar7 = *pbVar1;
    if (0x62 < bVar7) {
      if (bVar7 < bVar3) {
        bVar7 = *pbVar9;
      }
      *pbVar9 = bVar7;
    }
    pbVar9 = pbVar9 + 1;
    iVar8 = iVar8 + -1;
    pbVar10 = pbVar9;
  } while (iVar8 != 0);
  for (; param_4 != 0; param_4 = param_4 + -1) {
    pbVar1 = pbVar9;
    pbVar9 = pbVar9 + 1;
    *pbVar10 = *pbVar1;
    pbVar10 = pbVar10 + 1;
  }
  return;
}


// ---- FUN_1000_4201 @ 1000:4201 ----

void __cdecl16near FUN_1000_4201(undefined2 *param_1)

{
  uint uVar1;
  undefined2 unaff_DS;
  int local_8;
  int local_6;
  
  *(undefined2 *)0x4514 = *param_1;
  *(undefined2 *)0x9612 = param_1[3];
  if (((*(uint *)0x961c & 0xa000) == 0xa000) && (*(int *)0x3c == 0)) {
    FUN_1000_3d18(param_1[1],param_1[2]);
  }
  else {
    local_8 = param_1[1];
    local_6 = 0;
    for (uVar1 = 0; uVar1 < (uint)param_1[2]; uVar1 = uVar1 + 1) {
      FUN_1000_41a0(local_8,local_6,0,0);
      local_8 = local_8 + 0x140;
      local_6 = local_6 + param_1[3];
    }
  }
  return;
}


// ---- FUN_1000_427c @ 1000:427c ----

void __cdecl16near FUN_1000_427c(undefined2 *param_1)

{
  undefined2 unaff_DS;
  
  if (*(int *)0x3c != 0) {
    FUN_1000_6168(param_1[1],param_1[2],0,*param_1);
  }
  return;
}


// ---- FUN_1000_42af @ 1000:42af ----

void __cdecl16near FUN_1000_42af(undefined2 *param_1)

{
  undefined2 uVar1;
  uint uVar2;
  undefined2 unaff_DS;
  int local_c;
  int local_8;
  
  if (*(int *)0x3c == 0) {
    FUN_1000_3cb1(*param_1,param_1[1],0,param_1[3],param_1[2]);
  }
  else {
    local_c = param_1[1];
    uVar1 = *param_1;
    local_8 = 0;
    for (uVar2 = 0; uVar2 < (uint)param_1[2]; uVar2 = uVar2 + 1) {
      FUN_1000_6053(local_c,0xa000,local_8,uVar1,param_1[3]);
      local_c = local_c + 0x140;
      local_8 = local_8 + param_1[3];
    }
  }
  return;
}


// ---- FUN_1000_4331 @ 1000:4331 ----

void __cdecl16near FUN_1000_4331(uint *param_1,uint *param_2,uint param_3)

{
  undefined2 unaff_DS;
  char *local_10;
  byte *local_e;
  byte *local_a;
  int local_6;
  uint local_4;
  
  if (*(int *)0x3c != 0) {
    *(undefined2 *)0x1600 = 0;
    do {
      if (param_3 == 0) {
        local_6 = 100;
      }
      else {
        local_6 = (int)(((long)*(int *)0x1600 * 100 & 0xffffU) / (ulong)param_3);
      }
      if ((100 < local_6) || (*(int *)0x54a0 != 0)) {
        local_6 = 100;
      }
      local_10 = (char *)0x31a8;
      local_a = (byte *)((ulong)*param_1 << 0x10);
      local_e = (byte *)((ulong)*param_2 << 0x10);
      for (local_4 = 0; local_4 < param_1[2] * 3; local_4 = local_4 + 1) {
        *local_10 = *local_a + (char)((int)(((uint)*local_e - (uint)*local_a) * local_6) / 100);
        local_10 = local_10 + 1;
        local_a = (byte *)CONCAT22(local_a._2_2_,(byte *)local_a + 1);
        local_e = (byte *)CONCAT22(local_e._2_2_,(byte *)local_e + 1);
      }
      FUN_1000_6168(param_1[1],param_1[2],0x31a8);
      FUN_1000_4153();
    } while (local_6 != 100);
  }
  return;
}


// ---- FUN_1000_4459 @ 1000:4459 ----

void __cdecl16near FUN_1000_4459(uint param_1)

{
  undefined2 unaff_DS;
  
  *(undefined2 *)0x1600 = 0;
  while ((*(uint *)0x1600 < param_1 && (*(int *)0x54a0 == 0))) {
    FUN_1000_4153();
  }
  return;
}


// ---- FUN_1000_4485 @ 1000:4485 ----

void __cdecl16near FUN_1000_4485(int param_1,int param_2)

{
  undefined2 unaff_DS;
  
  FUN_1000_6053(param_1 + *(int *)(param_2 + 2) * 3);
  return;
}


// ---- FUN_1000_44be @ 1000:44be ----

void __cdecl16near
FUN_1000_44be(undefined2 param_1,undefined2 param_2,uint param_3,undefined2 param_4)

{
  undefined2 uVar1;
  undefined2 unaff_DS;
  
  uVar1 = *(undefined2 *)0x318a;
  *(undefined2 *)0x3184 = *(undefined2 *)0x3188;
  *(undefined2 *)0x3186 = uVar1;
  if ((param_3 & 0x80) != 0) {
    param_3 = param_3 & 0x7f;
    uVar1 = *(undefined2 *)0x318e;
    *(undefined2 *)0x3184 = *(undefined2 *)0x318c;
    *(undefined2 *)0x3186 = uVar1;
  }
  if (*(int *)0x3c == 0) {
    FUN_1000_3e8a(param_1,param_2,param_3,0xf);
  }
  else {
    FUN_1000_3c52(param_1,param_2,param_3,param_4);
  }
  return;
}


// ---- FUN_1000_4526 @ 1000:4526 ----

void __cdecl16near FUN_1000_4526(int param_1,undefined2 param_2,char *param_3,undefined2 param_4)

{
  undefined2 unaff_DS;
  
  while (*param_3 != '\0') {
    FUN_1000_44be(param_1,param_2,*param_3,param_4);
    param_1 = param_1 + 8;
    param_3 = param_3 + 1;
  }
  return;
}


// ---- FUN_1000_4563 @ 1000:4563 ----

void __cdecl16near FUN_1000_4563(int param_1,int param_2,int param_3)

{
  undefined2 unaff_DS;
  
  *(int *)0xbf6 = param_2 * 0x140 + param_1;
  *(int *)0xbfa = param_3 << 3;
  FUN_1000_3c9a();
  FUN_1000_4201(0xbf4);
  return;
}


// ---- FUN_1000_4591 @ 1000:4591 ----

int __cdecl16near FUN_1000_4591(void)

{
  bool bVar1;
  uint uVar2;
  uint uVar3;
  undefined2 uVar4;
  undefined2 uVar5;
  undefined2 unaff_DS;
  int local_e4;
  uint local_e0;
  uint local_de;
  undefined1 local_da [42];
  undefined1 local_b0 [42];
  undefined1 local_86 [18];
  undefined2 local_74 [3];
  undefined1 local_6e [6];
  undefined1 local_68 [4];
  int local_64;
  undefined1 local_62 [6];
  undefined1 local_5c [56];
  undefined2 local_24;
  int local_22;
  uint local_20;
  int local_1e;
  undefined2 local_14 [4];
  int local_c;
  int local_a;
  uint local_6;
  uint local_4;
  
  local_e4 = -1;
  FUN_1000_3f20();
  FUN_1000_57c4(0);
  FUN_1000_411b(0xd52);
  FUN_1000_3fe2(local_62,0);
  FUN_1000_4084(local_14,0);
  FUN_1000_3fe2(local_68,0x32);
  FUN_1000_3fe2(local_6e,0x32);
  FUN_1000_4084(&local_24,0x32);
  for (local_4 = 0; (int)local_4 < 7; local_4 = local_4 + 1) {
    FUN_1000_3fe2(local_b0 + local_4 * 6,0xa0);
    FUN_1000_3fe2(local_da + local_4 * 6,0xa0);
    FUN_1000_4084(local_5c + local_4 * 8,0xa0);
  }
  FUN_1000_413c();
  FUN_1000_411b(0xd5c);
  FUN_1000_6576();
  FUN_1000_6576();
  uVar2 = FUN_1000_6576();
  FUN_1000_3fe2(local_86,0);
  local_de = 0;
  for (local_4 = 0; local_4 < uVar2; local_4 = local_4 + 1) {
    uVar3 = FUN_1000_6576();
    for (local_e0 = 0; local_e0 < uVar3; local_e0 = local_e0 + 1) {
      *(uint *)(local_de * 10 + 0x45b6) = local_4;
      FUN_1000_4084(local_de * 10 + 0x45b8,0);
      local_de = local_de + 1;
      if (local_de == 300) {
        *(undefined2 *)0x41aa = 0x40;
        FUN_1000_0069();
      }
    }
  }
  FUN_1000_413c();
  uVar5 = *(undefined2 *)0x4560;
  uVar4 = FUN_1000_5c77(0xd66,0,uVar5,0x7d64);
  *(undefined2 *)0x41ac = uVar4;
  FUN_1000_5fb5(uVar4);
  FUN_1000_413c();
  *(undefined2 *)0x54a0 = 0;
  *(undefined2 *)0xaf32 = 1;
  FUN_1000_3c9a();
  FUN_1000_5d07(0x5174,0,0x300);
  FUN_1000_4b8e(0x5174,0,0);
  FUN_1000_4485(0x5174,local_86);
  FUN_1000_42af(local_14);
  FUN_1000_4b8e(0x5174,1,0x24);
  FUN_1000_4459(0x18);
  if (*(int *)0x54a0 == 0) {
    FUN_1000_5b76(0,uVar5,0x5a,0x7d64);
  }
  FUN_1000_4459(0x25);
  if (*(int *)0x54a0 == 0) {
    *(undefined2 *)0x1600 = 0;
    for (local_4 = 0; local_4 < local_de; local_4 = local_4 + 1) {
      if (*(int *)(local_4 * 10 + 0x45b6) != local_e4) {
        do {
        } while (*(uint *)0x1600 < 2);
        *(undefined2 *)0x1600 = 0;
        local_e4 = *(int *)(local_4 * 10 + 0x45b6);
      }
      FUN_1000_42af(local_4 * 10 + 0x45b8);
      FUN_1000_4153();
      if (*(int *)0x54a0 != 0) {
        FUN_1000_42af(local_14);
        break;
      }
    }
  }
  *(undefined2 *)0x9612 = 0x140;
  *(undefined2 *)0x4514 = local_24;
  FUN_1000_417e(local_14[0],0xa000,1,0);
  FUN_1000_4459(0x48);
  if (*(int *)0x3c == 0) {
    FUN_1000_4201(&local_24);
  }
  else {
    FUN_1000_427c(local_68);
    *(undefined2 *)0x1600 = 0;
    do {
      local_4 = 0x13f - (int)(((long)*(int *)0x1600 * 0x13f & 0xffffU) / 0x12);
      if (((int)local_4 < 0) || (*(int *)0x54a0 != 0)) {
        local_4 = 0;
      }
      local_a = local_22;
      local_c = 0;
      for (local_6 = 0; local_6 < local_20; local_6 = local_6 + 2) {
        FUN_1000_41a0(local_a,local_c,local_4,0);
        FUN_1000_41a0(local_a + 0x140,local_c + 0x140 + local_4,0,local_4);
        local_a = local_a + 0x280;
        local_c = local_c + local_1e * 2;
      }
    } while (local_4 != 0);
    FUN_1000_5ce3(local_74,local_68,6);
    uVar5 = FUN_1000_3ef4(local_64 * 3,0);
    local_74[0] = uVar5;
    FUN_1000_0069();
    FUN_1000_5cd1(0,uVar5,0x3f,local_64 * 3);
    if (*(int *)0x54a0 == 0) {
      FUN_1000_4331(local_68,local_74,5);
      FUN_1000_4459(9);
      FUN_1000_4331(local_74,local_6e,0x46);
    }
    else {
      FUN_1000_4331(local_68,local_6e,5);
    }
  }
  bVar1 = false;
  while (!bVar1) {
    local_4 = 1;
    while (((int)local_4 < 7 && (*(int *)0x54a0 == 0))) {
      FUN_1000_427c(local_b0 + local_4 * 6);
      FUN_1000_417e(local_14[0],0xa000,1,0);
      FUN_1000_4201(local_5c + local_4 * 8);
      FUN_1000_4331(local_b0 + local_4 * 6,local_da + local_4 * 6,0x32);
      FUN_1000_4459(0x32);
      if (*(int *)0x3c == 0) {
        FUN_1000_4459(100);
      }
      FUN_1000_4331(local_da + local_4 * 6,local_b0 + local_4 * 6,0x32);
      *(undefined1 *)0xaf3a = 0xff;
      FUN_1000_4201(local_5c + local_4 * 8);
      local_4 = local_4 + 1;
    }
    bVar1 = true;
  }
  local_4 = *(int *)0x54a0;
  *(undefined2 *)0x54a0 = 0;
  *(undefined2 *)0xaf32 = 0;
  if (local_4 == 0) {
    FUN_1000_4485(0x5174,local_62);
    FUN_1000_4485(0x5174,local_6e);
    FUN_1000_4b8e(0x5174,0,0x24);
  }
  FUN_1000_3f3b();
  return local_4;
}


// ---- FUN_1000_4acb @ 1000:4acb ----

void __cdecl16near FUN_1000_4acb(int param_1,undefined2 param_2)

{
  undefined2 unaff_DS;
  
  FUN_1000_417e(*(undefined2 *)0xaf22,0xa000,param_2,1);
  FUN_1000_4201(param_1 * 8 + 0x44c2);
  return;
}


// ---- FUN_1000_4afe @ 1000:4afe ----

void __cdecl16near FUN_1000_4afe(void)

{
  undefined2 uVar1;
  uint uVar2;
  undefined2 unaff_DS;
  
  for (uVar2 = 0; uVar2 < 5; uVar2 = uVar2 + 1) {
    uVar1 = 0xff;
    if ((uVar2 == *(uint *)0x4518) || (uVar2 == *(int *)0x451a + 3U)) {
      uVar1 = 1;
    }
    FUN_1000_4acb(uVar2 + 5,uVar1);
  }
  return;
}


// ---- FUN_1000_4b43 @ 1000:4b43 ----

void __cdecl16near FUN_1000_4b43(undefined2 *param_1,undefined2 param_2)

{
  undefined2 uVar1;
  undefined2 unaff_DS;
  
  uVar1 = FUN_1000_3ef4(0x300,0);
  *param_1 = uVar1;
  FUN_1000_0069();
  FUN_1000_6053(0,uVar1,param_2);
  param_1[1] = 0;
  param_1[2] = 0x100;
  return;
}


// ---- FUN_1000_4b8e @ 1000:4b8e ----

void __cdecl16near FUN_1000_4b8e(undefined2 param_1,int param_2,undefined2 param_3)

{
  undefined2 uVar1;
  undefined2 unaff_DS;
  undefined1 local_e [6];
  undefined1 local_8 [6];
  
  FUN_1000_5d07(0x31a8,0,0x300);
  if (*(int *)0x3c == 0) {
    FUN_1000_6006();
    if (param_2 == 0) {
      uVar1 = 0x31a8;
    }
    else {
      uVar1 = 0xbe0;
    }
    FUN_1000_61e4(uVar1);
    FUN_1000_6006();
  }
  else {
    FUN_1000_3f20();
    FUN_1000_4b43(local_8,param_1);
    FUN_1000_4b43(local_e,0x31a8);
    if (param_2 == 0) {
      FUN_1000_4331(local_8,local_e,param_3);
    }
    else {
      FUN_1000_4331(local_e,local_8,param_3);
    }
    FUN_1000_3f3b();
  }
  return;
}


// ---- FUN_1000_4c20 @ 1000:4c20 ----

void __cdecl16near FUN_1000_4c20(void)

{
  int iVar1;
  undefined2 unaff_DS;
  uint local_8;
  uint local_6;
  uint local_4;
  
  local_4 = 0;
  local_6 = 0;
  FUN_1000_3f20();
  FUN_1000_411b(0xd70);
  FUN_1000_3f91(0x5174,200);
  FUN_1000_4084(0xaf22,200);
  FUN_1000_3f91(0x5174,0xfa);
  for (local_8 = 0; local_8 < 10; local_8 = local_8 + 1) {
    FUN_1000_4084(local_8 * 8 + 0x44c2,0xfa);
  }
  FUN_1000_413c();
  FUN_1000_42af(0xaf22);
  FUN_1000_4afe();
  FUN_1000_4acb(0,1);
  FUN_1000_4b8e(0x5174,1,0x24);
  while( true ) {
    while( true ) {
      if (local_4 != local_6) {
        FUN_1000_4acb(local_6,0xff);
        local_6 = local_4;
        FUN_1000_4acb(local_4,1);
      }
      iVar1 = FUN_1000_5feb();
      if (iVar1 != 0xd) break;
      if (local_4 < 3) {
        *(uint *)0x4518 = local_4;
      }
      else {
        *(int *)0x451a = local_4 - 3;
      }
      if (*(int *)0x451a == 0) {
        FUN_1000_57c4(2);
      }
      else {
        FUN_1000_58a5();
        *(undefined2 *)0xbf2 = 0xffff;
      }
      FUN_1000_4afe();
    }
    if (iVar1 == 0x1b) break;
    if (iVar1 == 0x4800) {
      if (local_4 == 3) {
        local_4 = 0;
      }
      if (local_4 == 4) {
        local_4 = 1;
      }
    }
    else if (iVar1 == 0x4b00) {
      if (local_4 != 0) {
        local_4 = local_4 - 1;
      }
    }
    else if (iVar1 == 0x4d00) {
      if (local_4 < 4) {
        local_4 = local_4 + 1;
      }
    }
    else if (iVar1 == 0x5000) {
      if (local_4 == 0) {
        local_4 = 3;
      }
      else if (local_4 < 3) {
        local_4 = 4;
      }
    }
  }
  FUN_1000_3f3b();
  FUN_1000_578c();
  return;
}


// ---- FUN_1000_4dc8 @ 1000:4dc8 ----

bool __cdecl16near FUN_1000_4dc8(void)

{
  int iVar1;
  undefined1 local_a [8];
  
  FUN_1000_3f20();
  FUN_1000_3f91(0x5174,200);
  FUN_1000_4084(local_a,200);
  FUN_1000_42af(local_a);
  FUN_1000_4b8e(0x5174,1,0x24);
  FUN_1000_3f3b();
  iVar1 = FUN_1000_5feb();
  FUN_1000_4b8e(0x5174,0,0x24);
  return iVar1 != 0x1b;
}


// ---- FUN_1000_4e2e @ 1000:4e2e ----

void __cdecl16near FUN_1000_4e2e(void)

{
  int iVar1;
  
  FUN_1000_411b(0xd7c);
  iVar1 = FUN_1000_4dc8();
  if (iVar1 != 0) {
    FUN_1000_4dc8();
  }
  FUN_1000_413c();
  return;
}


// ---- FUN_1000_4e52 @ 1000:4e52 ----

void __cdecl16near FUN_1000_4e52(int param_1)

{
  int iVar1;
  uint uVar2;
  undefined2 unaff_DS;
  undefined1 local_3e [6];
  undefined1 local_38 [6];
  undefined1 local_32 [8];
  undefined1 local_2a [8];
  undefined2 local_22 [4];
  undefined1 local_1a [24];
  
  FUN_1000_3f20();
  FUN_1000_57c4(2);
  FUN_1000_411b(0xd8a);
  FUN_1000_3f91(0x5174,0xbe);
  for (uVar2 = 0; uVar2 < 3; uVar2 = uVar2 + 1) {
    FUN_1000_4084(local_1a + uVar2 * 8,0xbe);
  }
  FUN_1000_413c();
  FUN_1000_411b(0xd98);
  FUN_1000_3f91(0x5174,0);
  FUN_1000_4084(local_22,0);
  FUN_1000_3f20();
  FUN_1000_3f91(0x5174,0x32);
  FUN_1000_3f91(0x5174,0x32);
  FUN_1000_4084(local_2a,0x32);
  FUN_1000_3fe2(local_38,0xa0);
  FUN_1000_3fe2(local_3e,0xa0);
  FUN_1000_4084(local_32,0xa0);
  FUN_1000_413c();
  FUN_1000_417e(local_22[0],local_22[0],1,0);
  FUN_1000_4201(local_2a);
  FUN_1000_3c9a();
  if ((*(int *)0x3c != 0) && (param_1 == 0)) {
    FUN_1000_6168(0xbe,3,0x53ae);
  }
  if (param_1 != 0) {
    FUN_1000_42af(local_22);
    FUN_1000_4b8e(0x5174,1,0x24);
  }
  FUN_1000_427c(local_38);
  FUN_1000_417e(0,0xa000,0,1);
  if (*(int *)0x3c != 0) {
    FUN_1000_4201(local_32);
    FUN_1000_4331(local_38,local_3e,0x32);
  }
  FUN_1000_3f3b();
  uVar2 = 0;
  do {
    while( true ) {
      FUN_1000_417e(local_22[0],0xa000,1,0);
      FUN_1000_4201(local_1a + uVar2 * 8);
      iVar1 = FUN_1000_5feb();
      if (iVar1 != 0xd) break;
LAB_1000_5003:
      FUN_1000_4b8e(0x5174,0,0x24);
      if (uVar2 == 0) {
        FUN_1000_3f3b();
        return;
      }
      if (uVar2 == 1) {
        FUN_1000_4c20();
        FUN_1000_4b8e(0x5174,0,0x24);
      }
      else {
        FUN_1000_4e2e();
      }
      FUN_1000_42af(local_22);
      FUN_1000_4b8e(0x5174,1,0x24);
    }
    if (iVar1 == 0x1b) {
      FUN_1000_0046();
      goto LAB_1000_5003;
    }
    if (iVar1 == 0x4800) {
      if (uVar2 != 0) {
        uVar2 = uVar2 - 1;
      }
    }
    else if ((iVar1 == 0x5000) && (uVar2 < 2)) {
      uVar2 = uVar2 + 1;
    }
  } while( true );
}


// ---- FUN_1000_5080 @ 1000:5080 ----

void __cdecl16near FUN_1000_5080(uint param_1,int param_2,undefined2 param_3)

{
  undefined2 uVar1;
  undefined2 unaff_DS;
  uint local_10;
  undefined2 local_e;
  int local_c;
  undefined2 local_a;
  undefined2 local_8;
  int local_6;
  undefined2 local_4;
  
  FUN_1000_3f20();
  local_4 = FUN_1000_3ef4(0x1b0,0);
  local_6 = 0;
  FUN_1000_0069();
  if (*(int *)0x3c == 0) {
    uVar1 = 0xc;
  }
  else {
    uVar1 = 1;
  }
  FUN_1000_5cd1(local_6,local_4,uVar1,0x1b0);
  for (local_10 = 0x31; local_10 < 0x180; local_10 = local_10 + 0x30) {
    FUN_1000_5cd1(local_6 + local_10,local_4,0,0x2e);
  }
  local_e = local_4;
  local_a = 9;
  local_8 = 0x30;
  local_c = (int)(((ulong)param_1 / 3) % 5) * 0x30c0 + 0xf3e + (param_1 % 3) * 0xb40;
  if (0xe < param_1) {
    local_c = local_c + 0xa0;
  }
  if (param_2 == 0) {
    uVar1 = 0xff;
  }
  else {
    uVar1 = 0;
  }
  FUN_1000_417e(param_3,0xa000,uVar1,1);
  FUN_1000_4201(&local_e);
  FUN_1000_3f3b();
  return;
}


// ---- FUN_1000_5180 @ 1000:5180 ----

undefined2 __cdecl16near FUN_1000_5180(void)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  undefined2 unaff_DS;
  undefined2 local_20;
  uint local_1e;
  undefined1 local_12 [2];
  int local_10;
  undefined2 local_a [4];
  
  local_1e = 1000;
  FUN_1000_3f20();
  FUN_1000_57c4(2);
  FUN_1000_411b(0xda2);
  FUN_1000_3f91(0x5174,0);
  FUN_1000_4084(local_a,0);
  FUN_1000_3f91(0x5174,0xf0);
  FUN_1000_4084(local_12,0xf0);
  FUN_1000_413c();
  FUN_1000_3c9a();
  FUN_1000_417e(0,local_a[0],0,0);
  for (uVar2 = 0; uVar2 < 0x1e; uVar2 = uVar2 + 1) {
    iVar1 = (int)(((ulong)uVar2 % 0xf) / 3) * 0x30c0 + (int)(((ulong)uVar2 % 0xf) % 3) * 0xb40;
    local_10 = iVar1 + 0x11f0;
    if (0xe < uVar2) {
      local_10 = iVar1 + 0x1290;
    }
    for (uVar3 = 0; (uVar3 < *(uint *)(uVar2 * 2 + 0x451c) && (uVar3 < 7)); uVar3 = uVar3 + 1) {
      FUN_1000_4201(local_12);
      local_10 = local_10 + 7;
    }
  }
  FUN_1000_42af(local_a);
  FUN_1000_4b8e(0x5174,1,0x24);
  while( true ) {
    if (0x1d < *(uint *)0x9332) {
      *(undefined2 *)0x9332 = 0x1d;
    }
    if (*(uint *)0x9332 != local_1e) {
      if (local_1e < 1000) {
        FUN_1000_5080(local_1e,0,local_a[0]);
      }
      local_1e = *(uint *)0x9332;
      FUN_1000_5080(local_1e,1,local_a[0]);
    }
    iVar1 = FUN_1000_5feb();
    if (iVar1 == 0xd) break;
    if (iVar1 == 0x1b) {
      local_20 = 1;
LAB_1000_536d:
      FUN_1000_4b8e(0x5174,0,0x24);
      FUN_1000_3f3b();
      return local_20;
    }
    if (iVar1 == 0x4800) {
      if (*(int *)0x9332 != 0) {
        *(int *)0x9332 = *(int *)0x9332 + -1;
      }
    }
    else if (iVar1 == 0x4b00) {
      if (*(uint *)0x9332 < 0xf) {
        *(undefined2 *)0x9332 = 0;
      }
      else {
        *(int *)0x9332 = *(int *)0x9332 + -0xf;
      }
    }
    else if (iVar1 == 0x4d00) {
      *(int *)0x9332 = *(int *)0x9332 + 0xf;
    }
    else if (iVar1 == 0x5000) {
      *(int *)0x9332 = *(int *)0x9332 + 1;
    }
  }
  local_20 = 0;
  goto LAB_1000_536d;
}


// ---- FUN_1000_5387 @ 1000:5387 ----

void __cdecl16near FUN_1000_5387(undefined2 param_1)

{
  uint uVar1;
  undefined2 unaff_DS;
  undefined1 local_34 [5];
  undefined1 local_2f [37];
  undefined2 local_a [4];
  
  FUN_1000_5d33(local_34,0xdae);
  FUN_1000_5f52(local_2f,param_1);
  FUN_1000_5ef6(local_34,0xdb4);
  FUN_1000_411b(local_34);
  FUN_1000_3f91(0x41c2,0x8e);
  FUN_1000_4084(local_a,0x8e);
  FUN_1000_413c();
  *(undefined2 *)0x5170 = local_a[0];
  FUN_1000_5c96(local_a[0],4000);
  if (*(int *)0x41aa == 0) {
    FUN_1000_5cd1(0xac80,local_a[0],0,0x4d80);
    FUN_1000_417e(*(undefined2 *)0x5170,*(undefined2 *)0x5170,0,1);
    *(undefined2 *)0x9612 = 0x140;
    *(undefined2 *)0x4514 = *(undefined2 *)0x5498;
    for (uVar1 = 0; uVar1 < 0x58c0; uVar1 = uVar1 + 0x140) {
      FUN_1000_41a0(uVar1 + 0xa140,uVar1,0,0);
    }
    if (*(int *)0x3c == 0) {
      FUN_1000_3cb1(*(undefined2 *)0x5170,0,2,0x140,200);
      *(undefined2 *)0x5170 = 0xa400;
    }
  }
  return;
}


// ---- FUN_1000_5481 @ 1000:5481 ----

void __cdecl16near
FUN_1000_5481(undefined2 param_1,undefined2 param_2,int param_3,undefined2 *param_4)

{
  undefined2 uVar1;
  int iVar2;
  undefined2 uVar3;
  undefined2 unaff_DS;
  
  uVar1 = FUN_1000_5c77(param_1);
  iVar2 = FUN_1000_5ca6(uVar1,0,0,2);
  iVar2 = iVar2 + param_3 * -2;
  FUN_1000_60ee(uVar1);
  uVar3 = FUN_1000_3ef4(iVar2,0);
  param_4[1] = uVar3;
  *param_4 = 0;
  FUN_1000_0069();
  FUN_1000_5f7d(uVar1,param_2,param_3 << 1);
  FUN_1000_5fb5(uVar1,*param_4,param_4[1],iVar2);
  FUN_1000_5c59(uVar1);
  return;
}


// ---- FUN_1000_5508 @ 1000:5508 ----

void __cdecl16near FUN_1000_5508(void)

{
  undefined2 uVar1;
  
  FUN_1000_5481(0xdba,0x95f8,10,0x5474);
  FUN_1000_5481(0xdc8,0x5480,10,0x960e);
  FUN_1000_5481(0xdd6,0x4572,0x22,0x54a4);
  uVar1 = FUN_1000_5c77(0xde0);
  FUN_1000_5f7d(uVar1,0x961e,0x18fe);
  FUN_1000_5c11();
  FUN_1000_5c59(uVar1);
  return;
}


// ---- FUN_1000_5567 @ 1000:5567 ----

void __cdecl16near FUN_1000_5567(void)

{
  undefined2 uVar1;
  undefined2 unaff_DS;
  undefined2 local_a [4];
  
  FUN_1000_411b(0xdea);
  FUN_1000_3f91(0x41c2,0x48);
  FUN_1000_4084(local_a,0x48);
  *(undefined2 *)0xaf36 = local_a[0];
  *(undefined2 *)0xaf34 = 0;
  FUN_1000_413c();
  FUN_1000_411b(0xdf4);
  FUN_1000_3f91(0x41c2,0x5c);
  if (*(int *)0x3c == 0) {
    FUN_1000_3f20();
  }
  FUN_1000_4084(0x5498,0x5c);
  if (*(int *)0x3c == 0) {
    FUN_1000_3f3b();
    FUN_1000_4084(0x5498,0x5c);
  }
  FUN_1000_413c();
  uVar1 = FUN_1000_5c77(0xe00,0,*(undefined2 *)0x4560,0x7d64);
  *(undefined2 *)0x41ac = uVar1;
  FUN_1000_5fb5(uVar1);
  FUN_1000_5c11();
  FUN_1000_413c();
  return;
}


// ---- FUN_1000_5614 @ 1000:5614 ----

uint __cdecl16near FUN_1000_5614(int param_1)

{
  undefined2 uVar1;
  undefined2 unaff_DS;
  undefined2 local_8;
  uint local_6;
  undefined2 local_4;
  
  FUN_1000_5d07(0x162c,0,7000);
  local_4 = FUN_1000_5c77(0xe08);
  FUN_1000_5ca6(local_4,param_1 << 2,0,0);
  FUN_1000_5f7d(local_4,&local_8,2);
  FUN_1000_5f7d(local_4,&local_6,2);
  FUN_1000_5ca6(local_4,local_8,0,0);
  FUN_1000_6420(local_4,0,0x1000,0);
  uVar1 = FUN_1000_6576();
  *(undefined2 *)0x4562 = uVar1;
  uVar1 = FUN_1000_6576();
  *(undefined2 *)0x54a2 = uVar1;
  uVar1 = FUN_1000_6576();
  *(undefined2 *)0x4566 = uVar1;
  FUN_1000_6595(0x41c2);
  FUN_1000_66e6(0x162c);
  FUN_1000_5c59(local_4);
  return local_6 / 0xe;
}


// ---- FUN_1000_56df @ 1000:56df ----

bool __cdecl16near FUN_1000_56df(void)

{
  int iVar1;
  undefined2 unaff_DS;
  uint local_8;
  int local_6;
  
  local_6 = 0;
  for (local_8 = 1; local_8 < 0x21; local_8 = local_8 + 1) {
    local_6 = local_6 + (*(uint *)0x4518 ^ local_8);
  }
  iVar1 = *(int *)0x4516;
  if (local_6 != iVar1) {
    *(int *)0x4516 = local_6;
  }
  return local_6 != iVar1;
}


// ---- FUN_1000_5737 @ 1000:5737 ----

void __cdecl16near FUN_1000_5737(void)

{
  undefined2 uVar1;
  int iVar2;
  undefined2 unaff_DS;
  
  uVar1 = FUN_1000_5c77(0xbfc);
  FUN_1000_5f7d(uVar1,0x4516,0x42);
  FUN_1000_5c59(uVar1);
  if ((*(int *)0x41aa != 0) || (iVar2 = FUN_1000_56df(), iVar2 != 0)) {
    FUN_1000_5d07(0x4516,0,0x42);
  }
  *(undefined2 *)0x41aa = 0;
  return;
}


// ---- FUN_1000_578c @ 1000:578c ----

void __cdecl16near FUN_1000_578c(void)

{
  undefined2 uVar1;
  undefined2 unaff_DS;
  
  FUN_1000_56df();
  uVar1 = FUN_1000_5c6a(0xbfc,0);
  FUN_1000_60ab(uVar1,0x4516,0x42);
  FUN_1000_5c59(uVar1);
  *(undefined2 *)0x41aa = 0;
  return;
}


// ---- FUN_1000_57c4 @ 1000:57c4 ----

void __cdecl16near FUN_1000_57c4(int param_1)

{
  undefined2 uVar1;
  undefined2 unaff_DS;
  undefined2 local_8;
  int local_6;
  uint local_4;
  
  if ((*(int *)0xbf2 != param_1) && (FUN_1000_58a5(), *(int *)0x451a == 0)) {
    uVar1 = FUN_1000_5c77(0xe12);
    *(undefined2 *)0x41ac = uVar1;
    FUN_1000_5ca6(*(undefined2 *)0x41ac,param_1 * 6,0,0);
    FUN_1000_5f7d(*(undefined2 *)0x41ac,&local_8,6);
    FUN_1000_5ca6(*(undefined2 *)0x41ac,local_8,0,0);
    FUN_1000_6420(*(undefined2 *)0x41ac,0,0x1000,0);
    if (local_4 < 16000) {
      FUN_1000_66e6(0x54b0);
    }
    else {
      FUN_1000_5c26(0xff);
    }
    FUN_1000_413c();
    if (*(int *)0x41aa == 0) {
      FUN_1000_5a7d(local_6 * 0x10 + 0x54b0,0x54b0);
      *(int *)0xbf2 = param_1;
    }
  }
  return;
}


// ---- FUN_1000_5892 @ 1000:5892 ----

undefined1 __cdecl16near FUN_1000_5892(void)

{
  undefined1 in_AL;
  undefined1 uVar1;
  undefined1 in_AH;
  int iVar2;
  int in_DX;
  
  out(in_DX,in_AL);
  in(in_DX);
  in(in_DX);
  in(in_DX);
  in(in_DX);
  in(in_DX);
  in(in_DX);
  out(in_DX + 1,in_AH);
  iVar2 = 0x23;
  do {
    uVar1 = in(in_DX);
    iVar2 = iVar2 + -1;
  } while (iVar2 != 0);
  return uVar1;
}


// ---- FUN_1000_58a5 @ 1000:58a5 ----

void __cdecl16near FUN_1000_58a5(void)

{
  byte bVar1;
  char cVar2;
  undefined2 unaff_DS;
  
  *(undefined2 *)0x3196 = 0xcb0;
  *(undefined1 *)0x319a = 0xe0;
  bVar1 = 0x40;
  do {
    FUN_1000_5892();
    bVar1 = bVar1 + 1;
  } while (bVar1 < 0x56);
  cVar2 = '\a';
  do {
    FUN_1000_59cf();
    cVar2 = cVar2 + -1;
  } while (-1 < cVar2);
  return;
}


// ---- FUN_1000_58cd @ 1000:58cd ----

void __cdecl16near FUN_1000_58cd(void)

{
  byte bVar1;
  undefined2 unaff_DS;
  
  FUN_1000_58a5();
  FUN_1000_5892();
  FUN_1000_5892();
  FUN_1000_5892();
  *(undefined2 *)0x3194 = 0xc84;
  bVar1 = 7;
  do {
    FUN_1000_5919();
    *(int *)0x3194 = *(int *)0x3194 + 0xb;
    bVar1 = bVar1 + 1;
  } while (bVar1 < 0xb);
  FUN_1000_5892();
  FUN_1000_5892();
  FUN_1000_5892();
  FUN_1000_5892();
  return;
}


// ---- FUN_1000_5919 @ 1000:5919 ----

void __cdecl16near FUN_1000_5919(void)

{
  uint in_AX;
  uint uVar1;
  uint uVar2;
  undefined2 unaff_DS;
  
  FUN_1000_59cf();
  uVar2 = in_AX & 0xff;
  *(undefined1 *)(uVar2 + 0x319b) = (char)(in_AX >> 8);
  uVar1 = 0;
  do {
    FUN_1000_5892();
    uVar1 = uVar1 + 1;
  } while (uVar1 < 5);
  do {
    if (!CARRY1(*(byte *)(uVar2 + 0xc26),*(byte *)(uVar1 + 0xc10))) {
      FUN_1000_5892();
    }
    uVar1 = uVar1 + 1;
  } while (uVar1 < 10);
  if (*(char *)(uVar2 + 0xc31) != -1) {
    FUN_1000_5892();
  }
  return;
}


// ---- FUN_1000_59cf @ 1000:59cf ----

void FUN_1000_59cf(void)

{
  byte bVar1;
  byte in_AL;
  undefined2 unaff_DS;
  
  if (5 < in_AL) {
    bVar1 = in_AL - 6 & 7;
    *(byte *)0x319a = (0xefU >> bVar1 | -0x11 << 8 - bVar1) & *(byte *)0x319a;
  }
  FUN_1000_5892();
  return;
}


// ---- FUN_1000_5a7d @ 1000:5a7d ----

void __cdecl16near FUN_1000_5a7d(undefined2 param_1,undefined2 param_2)

{
  undefined2 unaff_DS;
  
  *(undefined2 *)0x3196 = param_1;
  *(undefined2 *)0x3198 = param_1;
  *(undefined2 *)0x3194 = param_2;
  *(undefined1 *)0x31a6 = 0;
  return;
}


// ---- FUN_1000_5a98 @ 1000:5a98 ----

undefined2 __cdecl16near FUN_1000_5a98(void)

{
  undefined1 uVar1;
  undefined1 uVar2;
  undefined1 uVar3;
  undefined1 uVar4;
  char cVar5;
  uint in_AX;
  byte bVar6;
  undefined2 unaff_DS;
  
  do {
    out(*(int *)0xcb6 + 6,1);
    out(0x43,0);
    uVar1 = in(0x40);
    uVar2 = in(0x40);
    do {
      out(0x43,0);
      uVar3 = in(0x40);
      uVar4 = in(0x40);
    } while ((uint)-(CONCAT11(uVar4,uVar3) - CONCAT11(uVar2,uVar1)) < 8);
    out(*(int *)0xcb6 + 6,0);
    out(0x43,0);
    uVar1 = in(0x40);
    uVar2 = in(0x40);
    in_AX = in_AX & 0xff00;
    do {
      bVar6 = (byte)(in_AX >> 8);
      cVar5 = in(*(int *)0xcb6 + 0xe);
      if ((cVar5 < '\0') && (cVar5 = in(*(int *)0xcb6 + 10), cVar5 == -0x56)) {
        do {
          cVar5 = in(*(int *)0xcb6 + 0xc);
        } while (cVar5 < '\0');
        out(*(int *)0xcb6 + 0xc,0xd1);
        return CONCAT11(bVar6,0xd1);
      }
      out(0x43,0);
      uVar3 = in(0x40);
      uVar4 = in(0x40);
      in_AX = (uint)bVar6 << 8;
    } while ((uint)-(CONCAT11(uVar4,uVar3) - CONCAT11(uVar2,uVar1)) < 0xf0);
    *(int *)0xcb6 = *(int *)0xcb6 + 0x10;
    if (0x260 < *(uint *)0xcb6) {
      *(undefined2 *)0xcb6 = 0;
      return 0;
    }
  } while( true );
}


// ---- FUN_1000_5b39 @ 1000:5b39 ----

undefined4 __cdecl16near FUN_1000_5b39(void)

{
  byte bVar1;
  int iVar2;
  undefined1 uVar3;
  undefined1 in_CL;
  undefined1 in_CH;
  uint in_DX;
  int iVar4;
  undefined2 uVar5;
  int in_BX;
  undefined2 unaff_DS;
  
  bVar1 = (byte)*(undefined2 *)0xcb8 | 4;
  out(10,bVar1);
  out(0xb,bVar1 ^ 0x5c);
  out(0xc,0);
  iVar2 = in_BX * 0x10 + in_DX;
  iVar4 = *(int *)0xcb8 * 2;
  out(iVar4,(char)iVar2);
  uVar3 = (undefined1)((uint)iVar2 >> 8);
  out(iVar4,uVar3);
  iVar4 = iVar4 + 1;
  out(iVar4,in_CL);
  out(iVar4,in_CH);
  uVar5 = CONCAT11((char)((uint)iVar4 >> 8),*(undefined1 *)(*(int *)0xcb8 + 0xcba));
  out(uVar5,(byte)((uint)in_BX >> 0xc) + CARRY2(in_BX * 0x10,in_DX));
  out(10,1);
  return CONCAT22(uVar5,CONCAT11(uVar3,1));
}


// ---- FUN_1000_5b76 @ 1000:5b76 ----

void __cdecl16near
FUN_1000_5b76(undefined2 param_1,undefined2 param_2,undefined1 param_3,int param_4)

{
  char cVar1;
  int iVar2;
  undefined2 unaff_DS;
  
  if (*(int *)0xcb6 != 0) {
    param_4 = param_4 + -1;
    FUN_1000_5b39();
    iVar2 = *(int *)0xcb6 + 0xc;
    do {
      cVar1 = in(iVar2);
    } while (cVar1 < '\0');
    out(iVar2,0x40);
    do {
      cVar1 = in(iVar2);
    } while (cVar1 < '\0');
    out(iVar2,param_3);
    do {
      cVar1 = in(iVar2);
    } while (cVar1 < '\0');
    out(iVar2,0x14);
    do {
      cVar1 = in(iVar2);
    } while (cVar1 < '\0');
    out(iVar2,(char)param_4);
    do {
      cVar1 = in(iVar2);
    } while (cVar1 < '\0');
    out(iVar2,(char)((uint)param_4 >> 8));
  }
  return;
}


// ---- FUN_1000_5bc0 @ 1000:5bc0 ----

void __cdecl16near FUN_1000_5bc0(void)

{
  char cVar1;
  int iVar2;
  undefined2 unaff_DS;
  
  if (*(int *)0xcb6 != 0) {
    iVar2 = *(int *)0xcb6 + 0xc;
    do {
      cVar1 = in(iVar2);
    } while (cVar1 < '\0');
    out(iVar2,0xd0);
    out(10,(byte)*(undefined2 *)0xcb8 | 4);
  }
  return;
}


// ---- FUN_1000_5bdb @ 1000:5bdb ----

undefined2 __cdecl16near FUN_1000_5bdb(void)

{
  code *pcVar1;
  undefined2 uVar2;
  undefined2 unaff_DS;
  bool bVar3;
  
  bVar3 = false;
  if (*(int *)0x41aa == 0) {
    pcVar1 = (code *)swi(0x21);
    uVar2 = (*pcVar1)();
    if (!bVar3) {
      return 0;
    }
    if (*(int *)0x41aa == 0) {
      *(undefined2 *)0x41aa = uVar2;
    }
  }
  return 0xffff;
}


// ---- FUN_1000_5bf8 @ 1000:5bf8 ----

undefined2 __cdecl16near FUN_1000_5bf8(void)

{
  code *pcVar1;
  undefined2 uVar2;
  undefined2 unaff_DS;
  bool bVar3;
  
  bVar3 = false;
  if (*(int *)0x41aa == 0) {
    pcVar1 = (code *)swi(0x21);
    uVar2 = (*pcVar1)();
    if (!bVar3) {
      return uVar2;
    }
    if (*(int *)0x41aa == 0) {
      *(undefined2 *)0x41aa = uVar2;
    }
  }
  return 0xffff;
}


// ---- FUN_1000_5c11 @ 1000:5c11 ----

void __cdecl16near FUN_1000_5c11(void)

{
  undefined2 unaff_DS;
  
  if ((*(int *)0x41aa == 0x12) || (*(int *)0x41aa == 0x14)) {
    *(undefined2 *)0x41aa = 0;
  }
  return;
}


// ---- FUN_1000_5c26 @ 1000:5c26 ----

void __cdecl16near FUN_1000_5c26(undefined2 param_1)

{
  undefined2 unaff_DS;
  
  if (*(int *)0x41aa == 0) {
    *(undefined2 *)0x41aa = param_1;
  }
  return;
}


// ---- FUN_1000_5c36 @ 1000:5c36 ----

void FUN_1000_5c36(void)

{
  FUN_1000_5bf8();
  return;
}


// ---- FUN_1000_5c59 @ 1000:5c59 ----

void __cdecl16near FUN_1000_5c59(void)

{
  code *pcVar1;
  undefined2 unaff_DS;
  
  if (*(int *)0x41aa != 0x15) {
    pcVar1 = (code *)swi(0x21);
    (*pcVar1)();
  }
  return;
}


// ---- FUN_1000_5c6a @ 1000:5c6a ----

void FUN_1000_5c6a(void)

{
  FUN_1000_5bf8();
  return;
}


// ---- FUN_1000_5c77 @ 1000:5c77 ----

void FUN_1000_5c77(void)

{
  FUN_1000_5bf8();
  return;
}


// ---- FUN_1000_5c82 @ 1000:5c82 ----

void __cdecl16near FUN_1000_5c82(char *param_1)

{
  char *pcVar1;
  undefined2 unaff_DS;
  
  while( true ) {
    pcVar1 = param_1;
    param_1 = param_1 + 1;
    if (*pcVar1 == '\0') break;
    FUN_1000_5fd4(*pcVar1);
  }
  return;
}


// ---- FUN_1000_5c96 @ 1000:5c96 ----

void __cdecl16near FUN_1000_5c96(void)

{
  FUN_1000_5bdb();
  return;
}


// ---- FUN_1000_5ca6 @ 1000:5ca6 ----

void __cdecl16near FUN_1000_5ca6(void)

{
  code *pcVar1;
  undefined2 uVar2;
  undefined2 unaff_DS;
  bool bVar3;
  
  bVar3 = false;
  if (*(int *)0x41aa == 0) {
    pcVar1 = (code *)swi(0x21);
    uVar2 = (*pcVar1)();
    if ((bVar3) && (*(int *)0x41aa == 0)) {
      *(undefined2 *)0x41aa = uVar2;
    }
  }
  return;
}


// ---- FUN_1000_5cd1 @ 1000:5cd1 ----

void __cdecl16near FUN_1000_5cd1(undefined1 *param_1,undefined1 param_2,int param_3)

{
  undefined1 *puVar1;
  undefined1 *puVar2;
  
  puVar2 = (undefined1 *)param_1;
  for (; param_3 != 0; param_3 = param_3 + -1) {
    puVar1 = puVar2;
    puVar2 = puVar2 + 1;
    *puVar1 = param_2;
  }
  return;
}


// ---- FUN_1000_5ce3 @ 1000:5ce3 ----

void __cdecl16near FUN_1000_5ce3(undefined1 *param_1,undefined1 *param_2,int param_3)

{
  undefined1 *puVar1;
  undefined1 *puVar2;
  undefined2 unaff_DS;
  byte bVar3;
  
  bVar3 = 0;
  if (param_2 <= param_1) {
    param_2 = param_2 + param_3 + -1;
    param_1 = param_1 + param_3 + -1;
    bVar3 = 1;
  }
  for (; param_3 != 0; param_3 = param_3 + -1) {
    puVar2 = param_1;
    param_1 = param_1 + (uint)bVar3 * -2 + 1;
    puVar1 = param_2;
    param_2 = param_2 + (uint)bVar3 * -2 + 1;
    *puVar2 = *puVar1;
  }
  return;
}


// ---- FUN_1000_5d07 @ 1000:5d07 ----

void __cdecl16near FUN_1000_5d07(undefined1 *param_1,undefined1 param_2,int param_3)

{
  undefined1 *puVar1;
  undefined2 unaff_DS;
  
  for (; param_3 != 0; param_3 = param_3 + -1) {
    puVar1 = param_1;
    param_1 = param_1 + 1;
    *puVar1 = param_2;
  }
  return;
}


// ---- FUN_1000_5d1b @ 1000:5d1b ----

char * __cdecl16near FUN_1000_5d1b(int param_1,char param_2)

{
  char *pcVar1;
  undefined2 unaff_DS;
  
  pcVar1 = (char *)(param_1 + -1);
  do {
    pcVar1 = pcVar1 + 1;
    if (*pcVar1 == param_2) {
      return pcVar1;
    }
  } while (*pcVar1 != '\0');
  return (char *)0x0;
}


// ---- FUN_1000_5d33 @ 1000:5d33 ----

void __cdecl16near FUN_1000_5d33(char *param_1,char *param_2)

{
  char *pcVar1;
  char *pcVar2;
  char cVar3;
  undefined2 unaff_DS;
  
  do {
    cVar3 = *param_2;
    pcVar2 = param_1;
    param_1 = param_1 + 1;
    pcVar1 = param_2;
    param_2 = param_2 + 1;
    *pcVar2 = *pcVar1;
  } while (cVar3 != '\0');
  return;
}


// ---- FUN_1000_5d4c @ 1000:5d4c ----

long FUN_1000_5d4c(uint param_1,int param_2,uint param_3,int param_4)

{
  if (param_4 == 0 && param_2 == 0) {
    return (ulong)param_1 * (ulong)param_3;
  }
  return CONCAT22((int)((ulong)param_1 * (ulong)param_3 >> 0x10) +
                  param_2 * param_3 + param_1 * param_4,(int)((ulong)param_1 * (ulong)param_3));
}


// ---- FUN_1000_5d80 @ 1000:5d80 ----

void __cdecl16near FUN_1000_5d80(void)

{
  uint in_CX;
  uint uVar1;
  
  for (uVar1 = in_CX & 0xff; uVar1 != 0; uVar1 = uVar1 - 1) {
  }
  return;
}


// ---- FUN_1000_5d8c @ 1000:5d8c ----

undefined4 FUN_1000_5d8c(uint param_1,uint param_2,uint param_3,uint param_4)

{
  ulong uVar1;
  long lVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  uint uVar9;
  
  uVar3 = param_1;
  uVar8 = param_4;
  uVar6 = param_2;
  uVar9 = param_3;
  if (param_4 == 0) {
    uVar3 = param_2 / param_3;
    iVar4 = (int)(((ulong)param_2 % (ulong)param_3 << 0x10 | (ulong)param_1) / (ulong)param_3);
  }
  else {
    do {
      uVar5 = uVar8 >> 1;
      uVar9 = uVar9 >> 1 | (uint)((uVar8 & 1) != 0) << 0xf;
      uVar7 = uVar6 >> 1;
      uVar3 = uVar3 >> 1 | (uint)((uVar6 & 1) != 0) << 0xf;
      uVar8 = uVar5;
      uVar6 = uVar7;
    } while (uVar5 != 0);
    uVar1 = CONCAT22(uVar7,uVar3) / (ulong)uVar9;
    iVar4 = (int)uVar1;
    lVar2 = (ulong)param_3 * (uVar1 & 0xffff);
    uVar3 = (uint)((ulong)lVar2 >> 0x10);
    uVar8 = uVar3 + iVar4 * param_4;
    if (((CARRY2(uVar3,iVar4 * param_4)) || (param_2 < uVar8)) ||
       ((param_2 <= uVar8 && (param_1 < (uint)lVar2)))) {
      iVar4 = iVar4 + -1;
    }
    uVar3 = 0;
  }
  return CONCAT22(uVar3,iVar4);
}


// ---- FUN_1000_5dee @ 1000:5dee ----

undefined4 FUN_1000_5dee(uint param_1,uint param_2,uint param_3,uint param_4)

{
  ulong uVar1;
  long lVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  int iVar6;
  int iVar7;
  uint uVar8;
  uint uVar9;
  uint uVar10;
  bool bVar11;
  
  uVar3 = param_1;
  uVar4 = param_4;
  uVar9 = param_2;
  uVar10 = param_3;
  if (param_4 == 0) {
    iVar6 = (int)(((ulong)param_2 % (ulong)param_3 << 0x10 | (ulong)param_1) % (ulong)param_3);
    iVar7 = 0;
  }
  else {
    do {
      uVar5 = uVar4 >> 1;
      uVar10 = uVar10 >> 1 | (uint)((uVar4 & 1) != 0) << 0xf;
      uVar8 = uVar9 >> 1;
      uVar3 = uVar3 >> 1 | (uint)((uVar9 & 1) != 0) << 0xf;
      uVar4 = uVar5;
      uVar9 = uVar8;
    } while (uVar5 != 0);
    uVar1 = CONCAT22(uVar8,uVar3) / (ulong)uVar10;
    uVar3 = (int)uVar1 * param_4;
    lVar2 = (uVar1 & 0xffff) * (ulong)param_3;
    uVar9 = (uint)((ulong)lVar2 >> 0x10);
    uVar4 = (uint)lVar2;
    uVar10 = uVar9 + uVar3;
    if (((CARRY2(uVar9,uVar3)) || (param_2 < uVar10)) || ((param_2 <= uVar10 && (param_1 < uVar4))))
    {
      bVar11 = uVar4 < param_3;
      uVar4 = uVar4 - param_3;
      uVar10 = (uVar10 - param_4) - (uint)bVar11;
    }
    iVar6 = -(uVar4 - param_1);
    iVar7 = -(uint)(uVar4 - param_1 != 0) - ((uVar10 - param_2) - (uint)(uVar4 < param_1));
  }
  return CONCAT22(iVar7,iVar6);
}


// ---- FUN_1000_5e5a @ 1000:5e5a ----

undefined4 FUN_1000_5e5a(uint param_1,uint param_2,uint param_3,uint param_4)

{
  ulong uVar1;
  long lVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  bool bVar10;
  char cVar11;
  uint uVar9;
  
  cVar11 = (int)param_2 < 0;
  if ((bool)cVar11) {
    bVar10 = param_1 != 0;
    param_1 = -param_1;
    param_2 = -(uint)bVar10 - param_2;
  }
  if ((int)param_4 < 0) {
    cVar11 = cVar11 + '\x01';
    bVar10 = param_3 != 0;
    param_3 = -param_3;
    param_4 = -(uint)bVar10 - param_4;
  }
  uVar3 = param_1;
  uVar5 = param_3;
  uVar6 = param_2;
  uVar9 = param_4;
  if (param_4 == 0) {
    uVar3 = param_2 / param_3;
    iVar4 = (int)(((ulong)param_2 % (ulong)param_3 << 0x10 | (ulong)param_1) / (ulong)param_3);
  }
  else {
    do {
      uVar8 = uVar9 >> 1;
      uVar5 = uVar5 >> 1 | (uint)((uVar9 & 1) != 0) << 0xf;
      uVar7 = uVar6 >> 1;
      uVar3 = uVar3 >> 1 | (uint)((uVar6 & 1) != 0) << 0xf;
      uVar6 = uVar7;
      uVar9 = uVar8;
    } while (uVar8 != 0);
    uVar1 = CONCAT22(uVar7,uVar3) / (ulong)uVar5;
    iVar4 = (int)uVar1;
    lVar2 = (ulong)param_3 * (uVar1 & 0xffff);
    uVar3 = (uint)((ulong)lVar2 >> 0x10);
    uVar5 = uVar3 + iVar4 * param_4;
    if (((CARRY2(uVar3,iVar4 * param_4)) || (param_2 < uVar5)) ||
       ((param_2 <= uVar5 && (param_1 < (uint)lVar2)))) {
      iVar4 = iVar4 + -1;
    }
    uVar3 = 0;
  }
  if (cVar11 == '\x01') {
    bVar10 = iVar4 != 0;
    iVar4 = -iVar4;
    uVar3 = -(uint)bVar10 - uVar3;
  }
  return CONCAT22(uVar3,iVar4);
}


// ---- FUN_1000_5ef6 @ 1000:5ef6 ----

void __cdecl16near FUN_1000_5ef6(undefined2 param_1,undefined2 param_2)

{
  undefined2 uVar1;
  
  uVar1 = FUN_1000_5d1b(param_1,0,param_2);
  FUN_1000_5d33(uVar1);
  return;
}


// ---- FUN_1000_5f0c @ 1000:5f0c ----

void __cdecl16near FUN_1000_5f0c(int param_1,undefined2 param_2,undefined2 param_3)

{
  char cVar1;
  char *pcVar2;
  undefined2 unaff_DS;
  long lVar3;
  
  lVar3 = CONCAT22(param_3,param_2);
  pcVar2 = (char *)(param_1 + 10);
  *pcVar2 = '\0';
  do {
    cVar1 = FUN_1000_5dee(lVar3,10,0);
    pcVar2 = pcVar2 + -1;
    *pcVar2 = cVar1 + '0';
    lVar3 = FUN_1000_5d8c(lVar3,10,0);
  } while (lVar3 != 0);
  FUN_1000_5d33(param_1,pcVar2);
  return;
}


// ---- FUN_1000_5f52 @ 1000:5f52 ----

void __cdecl16near FUN_1000_5f52(int param_1,uint param_2)

{
  ulong uVar1;
  char *pcVar2;
  undefined2 unaff_DS;
  
  pcVar2 = (char *)(param_1 + 5);
  *pcVar2 = '\0';
  do {
    pcVar2 = pcVar2 + -1;
    uVar1 = (ulong)param_2;
    param_2 = param_2 / 10;
    *pcVar2 = (char)(uVar1 % 10) + '0';
  } while (param_2 != 0);
  FUN_1000_5d33(param_1,pcVar2);
  return;
}


// ---- FUN_1000_5f7d @ 1000:5f7d ----

int __cdecl16near FUN_1000_5f7d(undefined2 param_1,undefined2 param_2,int param_3)

{
  code *pcVar1;
  int iVar2;
  undefined2 unaff_SS;
  bool bVar3;
  
  bVar3 = false;
  if (*(int *)0x41aa == 0) {
    pcVar1 = (code *)swi(0x21);
    iVar2 = (*pcVar1)();
    if (!bVar3) {
      if (iVar2 == param_3) {
        return iVar2;
      }
      *(undefined2 *)0x41aa = 0x14;
      return iVar2;
    }
    if (*(int *)0x41aa == 0) {
      *(int *)0x41aa = iVar2;
    }
  }
  return -1;
}


// ---- FUN_1000_5fb5 @ 1000:5fb5 ----

void __cdecl16near
FUN_1000_5fb5(undefined2 param_1,undefined2 param_2,undefined2 param_3,undefined2 param_4)

{
  FUN_1000_5f7d(param_1,param_2,param_4);
  return;
}


// ---- FUN_1000_5fcc @ 1000:5fcc ----

uint __cdecl16near FUN_1000_5fcc(void)

{
  code *pcVar1;
  uint uVar2;
  
  pcVar1 = (code *)swi(0x21);
  uVar2 = (*pcVar1)();
  return uVar2 & 1;
}


// ---- FUN_1000_5fd4 @ 1000:5fd4 ----

void __cdecl16near FUN_1000_5fd4(char param_1)

{
  code *pcVar1;
  
  if (param_1 == '\n') {
    pcVar1 = (code *)swi(0x21);
    (*pcVar1)();
  }
  pcVar1 = (code *)swi(0x21);
  (*pcVar1)();
  return;
}


// ---- FUN_1000_5feb @ 1000:5feb ----

uint __cdecl16near FUN_1000_5feb(void)

{
  code *pcVar1;
  byte bVar2;
  uint uVar3;
  
  pcVar1 = (code *)swi(0x21);
  bVar2 = (*pcVar1)();
  uVar3 = (uint)bVar2;
  if ((uVar3 == 0) || (bVar2 == 0xe0)) {
    pcVar1 = (code *)swi(0x21);
    bVar2 = (*pcVar1)();
    uVar3 = (uint)bVar2 << 8;
  }
  return uVar3;
}


// ---- FUN_1000_6001 @ 1000:6001 ----

void FUN_1000_6001(void)

{
  code *pcVar1;
  
  pcVar1 = (code *)swi(0x21);
  (*pcVar1)();
  FUN_1000_5f0c();
  FUN_1000_5c82();
  return;
}


// ---- FUN_1000_6006 @ 1000:6006 ----

void __cdecl16near FUN_1000_6006(void)

{
  byte bVar1;
  int iVar2;
  
  iVar2 = -1;
  do {
    bVar1 = in(iRam00000463 + 6);
    iVar2 = iVar2 + -1;
  } while (iVar2 != 0 && (bVar1 & 8) == 0);
  return;
}


// ---- FUN_1000_601d @ 1000:601d ----

void __cdecl16near FUN_1000_601d(void)

{
  code *pcVar1;
  
  pcVar1 = (code *)swi(0x10);
  (*pcVar1)();
  return;
}


// ---- FUN_1000_6027 @ 1000:6027 ----

undefined2 __cdecl16near FUN_1000_6027(void)

{
  code *pcVar1;
  undefined2 uVar2;
  byte bVar3;
  
  bVar3 = 0x10;
  pcVar1 = (code *)swi(0x10);
  (*pcVar1)();
  uVar2 = 0;
  if ((bVar3 != 0x10) && (2 < bVar3)) {
    uVar2 = 1;
  }
  return uVar2;
}


// ---- FUN_1000_603b @ 1000:603b ----

undefined2 __cdecl16near FUN_1000_603b(void)

{
  code *pcVar1;
  char cVar2;
  undefined2 uVar3;
  byte in_BL;
  
  pcVar1 = (code *)swi(0x10);
  cVar2 = (*pcVar1)();
  uVar3 = 0;
  if (((cVar2 == '\x1a') && (6 < in_BL)) && (in_BL < 9)) {
    uVar3 = 1;
  }
  return uVar3;
}


// ---- FUN_1000_6053 @ 1000:6053 ----

undefined1 * __cdecl16near FUN_1000_6053(undefined1 *param_1,undefined1 *param_2,int param_3)

{
  undefined1 *puVar1;
  undefined1 *puVar2;
  uint uVar3;
  byte bVar4;
  byte bVar5;
  undefined1 *puVar6;
  undefined1 *puVar7;
  undefined1 *puVar8;
  int iVar9;
  int iVar10;
  byte bVar11;
  
  bVar11 = 0;
  iVar9 = (int)((ulong)param_1 >> 0x10);
  puVar7 = (undefined1 *)param_1;
  iVar10 = (int)((ulong)param_2 >> 0x10);
  puVar6 = (undefined1 *)param_2;
  uVar3 = iVar10 * 0x10;
  bVar4 = (byte)((ulong)param_2 >> 0x1c) + CARRY2(uVar3,(uint)puVar6);
  bVar5 = (byte)((ulong)param_1 >> 0x1c) + CARRY2(iVar9 * 0x10,(uint)puVar7);
  puVar8 = puVar7;
  if ((bVar4 <= bVar5) && ((bVar4 < bVar5 || (puVar6 + uVar3 <= puVar7 + iVar9 * 0x10)))) {
    puVar6 = puVar6 + param_3 + -1;
    puVar7 = puVar7 + param_3 + -1;
    bVar11 = 1;
    puVar8 = puVar7;
  }
  for (; param_3 != 0; param_3 = param_3 + -1) {
    puVar2 = puVar7;
    puVar7 = puVar7 + (uint)bVar11 * -2 + 1;
    puVar1 = puVar6;
    puVar6 = puVar6 + (uint)bVar11 * -2 + 1;
    *puVar2 = *puVar1;
  }
  return (undefined1 *)CONCAT22(iVar9,puVar8);
}


// ---- FUN_1000_609f @ 1000:609f ----

void __cdecl16near FUN_1000_609f(void)

{
  code *pcVar1;
  
  pcVar1 = (code *)swi(0x21);
  (*pcVar1)();
  return;
}


// ---- FUN_1000_60ab @ 1000:60ab ----

int __cdecl16near FUN_1000_60ab(undefined2 param_1,undefined2 param_2,int param_3)

{
  code *pcVar1;
  int iVar2;
  undefined2 unaff_SS;
  bool bVar3;
  
  if (*(int *)0x41aa == 0) {
    bVar3 = false;
    if (param_3 == 0) {
      return 0;
    }
    pcVar1 = (code *)swi(0x21);
    iVar2 = (*pcVar1)();
    if (!bVar3) {
      if (iVar2 == param_3) {
        return iVar2;
      }
      *(undefined2 *)0x41aa = 0x13;
      return iVar2;
    }
    if (*(int *)0x41aa == 0) {
      *(int *)0x41aa = iVar2;
    }
  }
  return -1;
}


// ---- FUN_1000_60e9 @ 1000:60e9 ----

void FUN_1000_60e9(undefined2 param_1)

{
  FUN_1000_6001(1);
  FUN_1000_5ca6(param_1,0,0,0);
  return;
}


// ---- FUN_1000_60ee @ 1000:60ee ----

void __cdecl16near FUN_1000_60ee(undefined2 param_1)

{
  FUN_1000_5ca6(param_1,0,0,0);
  return;
}


// ---- FUN_1000_6151 @ 1000:6151 ----

byte __cdecl16near FUN_1000_6151(void)

{
  byte bVar1;
  byte in_AH;
  
  out(0x3c4,1);
  bVar1 = in(0x3c5);
  bVar1 = bVar1 & 0xdf | in_AH;
  out(0x3c5,bVar1);
  return bVar1;
}


// ---- FUN_1000_6168 @ 1000:6168 ----

undefined4 __cdecl16near FUN_1000_6168(int param_1,uint param_2,undefined1 *param_3)

{
  code *pcVar1;
  byte bVar2;
  undefined2 in_AX;
  int iVar3;
  undefined2 in_DX;
  undefined1 *puVar4;
  undefined1 *puVar5;
  int iVar6;
  undefined2 uVar7;
  bool bVar8;
  
  bVar8 = false;
  uVar7 = (undefined2)((ulong)param_3 >> 0x10);
  puVar4 = (undefined1 *)param_3;
  if ((bRam00000489 & 6) != 0) {
    pcVar1 = (code *)swi(0x10);
    (*pcVar1)();
LAB_1000_61e0:
    return CONCAT22(in_DX,in_AX);
  }
  iVar6 = iRam00000463 + 6;
  do {
    iVar3 = -1;
    do {
      bVar2 = in(iVar6);
      iVar3 = iVar3 + -1;
    } while (iVar3 != 0 && (bVar2 & 8) == 0);
    FUN_1000_6151();
    do {
      do {
        out(0x3c8,(char)param_1);
        puVar5 = puVar4 + (uint)bVar8 * -2 + 1;
        out(0x3c9,*puVar4);
        out(0x3c9,*puVar5);
        puVar4 = puVar5 + (uint)bVar8 * -2 + 1 + (uint)bVar8 * -2 + 1;
        out(0x3c9,puVar5[(uint)bVar8 * -2 + 1]);
        param_1 = param_1 + 1;
        param_2 = param_2 - 1;
      } while ((param_2 & 0x3f) != 0);
      if (param_2 == 0) {
        FUN_1000_6151();
        goto LAB_1000_61e0;
      }
      bVar2 = in(iVar6);
    } while ((bVar2 & 8) != 0);
    FUN_1000_6151();
    bVar8 = bVar8 != false;
  } while( true );
}


// ---- FUN_1000_61e4 @ 1000:61e4 ----

void __cdecl16near FUN_1000_61e4(void)

{
  code *pcVar1;
  
  pcVar1 = (code *)swi(0x10);
  (*pcVar1)();
  return;
}


// ---- entry @ 1000:61f3 ----

/* WARNING: Stack frame is not setup normally: Input value of stackpointer is not used */
/* WARNING: This function may have set the stack pointer */

void __cdecl16far entry(void)

{
  char cVar1;
  char *pcVar2;
  char *pcVar3;
  undefined1 *puVar4;
  code *pcVar5;
  undefined2 uVar6;
  int iVar7;
  uint uVar8;
  int iVar9;
  undefined1 *puVar10;
  undefined1 *puVar11;
  char *pcVar12;
  char *pcVar13;
  char *pcVar14;
  int iVar15;
  char *pcVar16;
  char *pcVar17;
  undefined1 *puVar18;
  undefined2 unaff_ES;
  undefined2 uVar19;
  
  puVar10 = (undefined1 *)0x800;
  pcVar5 = (code *)swi(0x21);
  DAT_1676_0cc0 = unaff_ES;
  uVar6 = (*pcVar5)();
  DAT_1676_0cbe = CONCAT11((byte)uVar6,(char)((uint)uVar6 >> 8));
  if (2 < (byte)uVar6) {
    if (DAT_1676_0cbe >> 1 != 0) {
      puVar11 = puVar10 + -0x4ec0;
      pcVar5 = (code *)swi(0x21);
      (*pcVar5)();
      uVar6 = *(undefined2 *)0x2c;
      pcVar14 = (char *)0x0;
      iVar7 = -0x8000;
code_r0x0001624e:
      do {
        pcVar16 = pcVar14;
        if (iVar7 != 0) {
          iVar7 = iVar7 + -1;
          pcVar2 = pcVar14;
          pcVar14 = pcVar14 + 1;
          pcVar16 = pcVar14;
          if (*pcVar2 != '\0') goto code_r0x0001624e;
        }
        pcVar14 = pcVar16 + 1;
      } while (*pcVar16 != '\0');
      pcVar16 = pcVar16 + 3;
      iVar7 = 0x100;
      pcVar14 = pcVar16;
      do {
        if (iVar7 == 0) break;
        iVar7 = iVar7 + -1;
        pcVar2 = pcVar14;
        pcVar14 = pcVar14 + 1;
      } while (*pcVar2 != '\0');
      iVar15 = (int)pcVar14 - (int)pcVar16;
      iVar7 = -iVar15;
      pcVar14 = puVar11 + iVar7;
      *(undefined2 *)(puVar11 + iVar7 + -2) = 0x1676;
      uVar19 = *(undefined2 *)(puVar11 + iVar7 + -2);
      for (; iVar15 != 0; iVar15 = iVar15 + -1) {
        pcVar3 = pcVar14;
        pcVar14 = pcVar14 + 1;
        pcVar2 = pcVar16;
        pcVar16 = pcVar16 + 1;
        *pcVar3 = *pcVar2;
      }
      *(undefined2 *)(puVar11 + iVar7 + -2) = 0x1676;
      uVar6 = *(undefined2 *)0xcc0;
      pcVar14 = (char *)0x81;
      uVar8 = (uint)*(byte *)0x80;
      pcVar16 = (char *)((uint)(puVar11 + (iVar7 - uVar8) + -1) & 0xfffe);
      iVar15 = 0;
      pcVar17 = pcVar16;
      if (uVar8 != 0) {
        for (; uVar8 != 0; uVar8 = uVar8 - 1) {
          pcVar2 = pcVar14;
          pcVar14 = pcVar14 + 1;
          *pcVar17 = *pcVar2;
          pcVar17 = pcVar17 + 1;
        }
        *pcVar17 = '\0';
        *(undefined2 *)(pcVar16 + -2) = 0x1676;
        uVar6 = *(undefined2 *)(pcVar16 + -2);
        iVar15 = 0;
        pcVar14 = pcVar16;
        while( true ) {
          do {
            do {
              pcVar2 = pcVar14;
              pcVar14 = pcVar14 + 1;
              cVar1 = *pcVar2;
            } while (cVar1 == ' ');
          } while (cVar1 == '\t');
          if ((cVar1 == '\r') || (cVar1 == '\0')) break;
          iVar15 = iVar15 + 1;
          do {
            pcVar17 = pcVar14;
            pcVar14 = pcVar17 + 1;
            cVar1 = *pcVar17;
            if ((cVar1 == '\r') || (cVar1 == '\0')) goto LAB_1000_62c6;
          } while ((cVar1 != ' ') && (cVar1 != '\t'));
          *pcVar17 = '\0';
        }
LAB_1000_62c6:
        pcVar14 = pcVar14 + -1;
        *pcVar14 = '\0';
        for (iVar9 = iVar15; iVar9 != 0; iVar9 = iVar9 + -1) {
          do {
            do {
              pcVar2 = pcVar14;
              pcVar14 = pcVar14 + -1;
              cVar1 = *pcVar2;
            } while (cVar1 == ' ');
          } while ((cVar1 == '\t') || (cVar1 == '\0'));
          while( true ) {
            pcVar2 = pcVar14;
            pcVar17 = pcVar14 + 1;
            pcVar14 = pcVar14 + -1;
            cVar1 = *pcVar2;
            if (cVar1 == ' ') break;
            if ((cVar1 == '\t') || (cVar1 == '\0')) break;
          }
          pcVar12 = pcVar16 + -2;
          pcVar16 = pcVar16 + -2;
          *(char **)pcVar12 = pcVar17;
        }
      }
      *(int *)(pcVar16 + -2) = (int)puVar11 + iVar7;
      *(char **)(pcVar16 + -4) = pcVar16 + -2;
      pcVar13 = pcVar16 + -6;
      *(int *)(pcVar16 + -6) = iVar15 + 1;
      *(undefined2 *)(pcVar16 + -8) = 0x1676;
      uVar6 = *(undefined2 *)(pcVar16 + -8);
      puVar18 = (undefined1 *)0xe1c;
      for (iVar7 = -0x5cdc; iVar7 != 0; iVar7 = iVar7 + -1) {
        puVar4 = puVar18;
        puVar18 = puVar18 + 1;
        *puVar4 = 0;
      }
      *(undefined2 *)(pcVar16 + -8) = 0x630b;
      FUN_1000_01b8();
      pcVar5 = (code *)swi(0x21);
      (*pcVar5)();
      *(undefined2 *)(pcVar13 + -2) = *(undefined2 *)(pcVar13 + 4);
      *(undefined2 *)(pcVar13 + -4) = *(undefined2 *)(pcVar13 + 2);
      *(undefined2 *)(pcVar13 + -6) = 7;
      *(undefined2 *)(pcVar13 + -8) = 0x631d;
      uVar6 = FUN_1000_5f0c();
      *(undefined2 *)(pcVar13 + -8) = uVar6;
      *(undefined2 *)(pcVar13 + -10) = 0x6321;
      FUN_1000_5c82();
      return;
    }
    pcVar5 = (code *)swi(0x21);
    (*pcVar5)();
  }
  *(undefined2 *)(puVar10 + -2) = unaff_ES;
  *(undefined2 *)(puVar10 + -4) = 0;
  return;
}


// ---- FUN_1000_630f @ 1000:630f ----

void __cdecl16near FUN_1000_630f(undefined2 param_1,undefined2 param_2)

{
  undefined2 uVar1;
  
  uVar1 = FUN_1000_5f0c(7,param_1,param_2);
  FUN_1000_5c82(uVar1);
  return;
}


// ---- FUN_1000_6326 @ 1000:6326 ----

void __cdecl16near FUN_1000_6326(void)

{
  undefined1 *puVar1;
  int iVar2;
  undefined2 uVar3;
  int iVar4;
  undefined2 unaff_DS;
  
  if (*(int *)0x41b6 != *(int *)0x41b4) {
    puVar1 = (undefined1 *)*(undefined2 *)0x41b6;
    *(int *)0x41b6 = *(int *)0x41b6 + 1;
    *(undefined1 *)0x41b0 = *puVar1;
    return;
  }
  if (*(char *)0x41bb != '\0') {
    FUN_1000_5c26(0x14);
    return;
  }
  uVar3 = FUN_1000_63d3();
  *(undefined2 *)0x41b8 = uVar3;
  iVar4 = *(int *)0x41b4;
  iVar2 = *(int *)0x41b2;
  *(int *)0x41b6 = iVar2;
  iVar4 = FUN_1000_5f7d(*(undefined2 *)0x41ac,iVar2,iVar4 - iVar2);
  if (iVar4 == 0) {
    iVar4 = 1;
    *(undefined1 *)0x41bb = 1;
  }
  *(int *)0x41b4 = iVar4 + *(int *)0x41b2;
  FUN_1000_5c11();
  puVar1 = (undefined1 *)*(undefined2 *)0x41b6;
  *(int *)0x41b6 = *(int *)0x41b6 + 1;
  *(undefined1 *)0x41b0 = *puVar1;
  *(undefined2 *)0x41ae = 8;
  return;
}


// ---- FUN_1000_633d @ 1000:633d ----

void __cdecl16near FUN_1000_633d(void)

{
  undefined2 unaff_DS;
  
  if (*(int *)0x41b6 == *(int *)0x41b4) {
    FUN_1000_63a3();
    *(undefined2 *)0x41b6 = *(undefined2 *)0x41b2;
  }
  return;
}


// ---- FUN_1000_6350 @ 1000:6350 ----

void __cdecl16near FUN_1000_6350(void)

{
  int iVar1;
  undefined1 *puVar2;
  undefined2 uVar3;
  int iVar4;
  undefined2 unaff_DS;
  
  if (*(char *)0x41bb != '\0') {
    FUN_1000_5c26(0x14);
    return;
  }
  uVar3 = FUN_1000_63d3();
  *(undefined2 *)0x41b8 = uVar3;
  iVar4 = *(int *)0x41b4;
  iVar1 = *(int *)0x41b2;
  *(int *)0x41b6 = iVar1;
  iVar4 = FUN_1000_5f7d(*(undefined2 *)0x41ac,iVar1,iVar4 - iVar1);
  if (iVar4 == 0) {
    iVar4 = 1;
    *(undefined1 *)0x41bb = 1;
  }
  *(int *)0x41b4 = iVar4 + *(int *)0x41b2;
  FUN_1000_5c11();
  puVar2 = (undefined1 *)*(undefined2 *)0x41b6;
  *(int *)0x41b6 = *(int *)0x41b6 + 1;
  *(undefined1 *)0x41b0 = *puVar2;
  *(undefined2 *)0x41ae = 8;
  return;
}


// ---- FUN_1000_6364 @ 1000:6364 ----

void __cdecl16near FUN_1000_6364(void)

{
  int iVar1;
  undefined1 *puVar2;
  int iVar3;
  undefined2 unaff_DS;
  
  iVar3 = *(int *)0x41b4;
  iVar1 = *(int *)0x41b2;
  *(int *)0x41b6 = iVar1;
  iVar3 = FUN_1000_5f7d(*(undefined2 *)0x41ac,iVar1,iVar3 - iVar1);
  if (iVar3 == 0) {
    iVar3 = 1;
    *(undefined1 *)0x41bb = 1;
  }
  *(int *)0x41b4 = iVar3 + *(int *)0x41b2;
  FUN_1000_5c11();
  puVar2 = (undefined1 *)*(undefined2 *)0x41b6;
  *(int *)0x41b6 = *(int *)0x41b6 + 1;
  *(undefined1 *)0x41b0 = *puVar2;
  *(undefined2 *)0x41ae = 8;
  return;
}


// ---- FUN_1000_63a3 @ 1000:63a3 ----

void __cdecl16near FUN_1000_63a3(void)

{
  undefined2 uVar1;
  undefined2 unaff_DS;
  
  FUN_1000_60ab(*(undefined2 *)0x41ac,*(int *)0x41b2,*(int *)0x41b6 - *(int *)0x41b2);
  uVar1 = FUN_1000_63bf();
  *(undefined2 *)0x41b8 = uVar1;
  return;
}


// ---- FUN_1000_63bf @ 1000:63bf ----

void __cdecl16near FUN_1000_63bf(void)

{
  int iVar1;
  undefined2 unaff_DS;
  
  iVar1 = *(int *)0x41b6;
  if ((*(char *)0x41ba == '\0') && (*(int *)0x41ae == 8)) {
    iVar1 = iVar1 + -1;
  }
  if (*(char *)0x41bc != '\0') {
    FUN_1000_669c(*(int *)0x41b2,iVar1 - *(int *)0x41b2,*(undefined2 *)0x41b8);
  }
  return;
}


// ---- FUN_1000_63d3 @ 1000:63d3 ----

void __cdecl16near FUN_1000_63d3(void)

{
  undefined2 unaff_DS;
  
  if (*(char *)0x41bc != '\0') {
    FUN_1000_669c(*(int *)0x41b2,*(int *)0x41b4 - *(int *)0x41b2,*(undefined2 *)0x41b8);
  }
  return;
}


// ---- FUN_1000_63f0 @ 1000:63f0 ----

void __cdecl16near FUN_1000_63f0(int param_1,uint param_2)

{
  uint uVar1;
  int iVar2;
  undefined2 unaff_DS;
  
  iVar2 = param_1 + 0x31a8;
  *(int *)0x41b2 = iVar2;
  *(int *)0x41b6 = iVar2;
  uVar1 = 0x1000U - param_1;
  if (param_2 <= 0x1000U - param_1) {
    uVar1 = param_2;
  }
  *(int *)0x41b4 = uVar1 + iVar2;
  *(undefined2 *)0x41b8 = 0;
  return;
}


// ---- FUN_1000_6420 @ 1000:6420 ----

void __cdecl16near
FUN_1000_6420(undefined2 param_1,undefined2 param_2,undefined2 param_3,undefined1 param_4)

{
  undefined2 unaff_DS;
  
  *(undefined2 *)0x41ac = param_1;
  *(undefined1 *)0x41bc = param_4;
  *(undefined1 *)0x41bb = 0;
  FUN_1000_63f0(param_2,param_3);
  FUN_1000_6364();
  *(undefined1 *)0x41ba = 0;
  return;
}


// ---- FUN_1000_644a @ 1000:644a ----

void __cdecl16near
FUN_1000_644a(undefined2 param_1,undefined2 param_2,undefined2 param_3,undefined1 param_4)

{
  undefined2 unaff_DS;
  
  *(undefined2 *)0x41ac = param_1;
  *(undefined1 *)0x41bc = param_4;
  FUN_1000_63f0(param_2,param_3);
  *(undefined2 *)0x41ae = 8;
  *(undefined1 *)0x41ba = 1;
  return;
}


// ---- FUN_1000_6490 @ 1000:6490 ----

undefined2 __cdecl16near FUN_1000_6490(void)

{
  undefined2 uVar1;
  undefined2 unaff_DS;
  
  uVar1 = *(undefined2 *)0x41b0;
  FUN_1000_6326();
  return uVar1;
}


// ---- FUN_1000_6499 @ 1000:6499 ----

void FUN_1000_6499(undefined1 param_1)

{
  undefined2 unaff_DS;
  
  *(undefined1 *)*(undefined2 *)0x41b6 = param_1;
  *(int *)0x41b6 = *(int *)0x41b6 + 1;
  FUN_1000_633d();
  return;
}


// ---- FUN_1000_64ab @ 1000:64ab ----

bool __cdecl16near FUN_1000_64ab(void)

{
  char *pcVar1;
  int *piVar2;
  char cVar3;
  undefined1 *puVar4;
  undefined2 unaff_DS;
  
  pcVar1 = (char *)0x41b0;
  cVar3 = *pcVar1;
  *pcVar1 = *pcVar1 << 1;
  piVar2 = (int *)0x41ae;
  *piVar2 = *piVar2 + -1;
  if (*piVar2 == 0) {
    *(undefined2 *)0x41ae = 8;
    puVar4 = (undefined1 *)*(undefined2 *)0x41b6;
    *(int *)0x41b6 = *(int *)0x41b6 + 1;
    if ((undefined1 *)*(undefined2 *)0x41b4 == puVar4) {
      FUN_1000_6350();
    }
    else {
      *(undefined1 *)0x41b0 = *puVar4;
    }
  }
  return cVar3 < '\0';
}


// ---- FUN_1000_64ff @ 1000:64ff ----

void __cdecl16near FUN_1000_64ff(int param_1)

{
  char *pcVar1;
  int *piVar2;
  char cVar3;
  undefined1 *puVar4;
  uint uVar5;
  uint uVar6;
  undefined2 unaff_DS;
  
  uVar5 = 0;
  while (param_1 = param_1 + -1, -1 < param_1) {
    pcVar1 = (char *)0x41b0;
    cVar3 = *pcVar1;
    *pcVar1 = *pcVar1 << 1;
    uVar6 = (uint)(cVar3 < '\0');
    piVar2 = (int *)0x41ae;
    *piVar2 = *piVar2 + -1;
    if (*piVar2 == 0) {
      *(undefined2 *)0x41ae = 8;
      puVar4 = (undefined1 *)*(undefined2 *)0x41b6;
      *(int *)0x41b6 = *(int *)0x41b6 + 1;
      if ((undefined1 *)*(undefined2 *)0x41b4 == puVar4) {
        FUN_1000_6350(param_1,uVar6,uVar5);
      }
      else {
        *(undefined1 *)0x41b0 = *puVar4;
      }
    }
    uVar5 = uVar5 | uVar6 << ((byte)param_1 & 0x1f);
  }
  return;
}


// ---- FUN_1000_6576 @ 1000:6576 ----

undefined2 __cdecl16near FUN_1000_6576(void)

{
  undefined1 uVar1;
  undefined1 uVar2;
  
  uVar1 = FUN_1000_6490();
  uVar2 = FUN_1000_6490();
  return CONCAT11(uVar2,uVar1);
}


// ---- FUN_1000_6595 @ 1000:6595 ----

void __cdecl16near FUN_1000_6595(undefined1 *param_1,int param_2)

{
  uint uVar1;
  uint uVar2;
  undefined1 *puVar3;
  undefined2 uVar4;
  undefined2 unaff_DS;
  
  if (*(int *)0x41aa == 0) {
    uVar4 = (undefined2)((ulong)param_1 >> 0x10);
    puVar3 = (undefined1 *)param_1;
    while (param_2 != 0) {
      uVar2 = param_2 - 1;
      *puVar3 = (char)*(undefined2 *)0x41b0;
      uVar1 = *(int *)0x41b4 - *(int *)0x41b6;
      if (uVar2 <= (uint)(*(int *)0x41b4 - *(int *)0x41b6)) {
        uVar1 = uVar2;
      }
      FUN_1000_6053(puVar3 + 1,uVar4,*(undefined2 *)0x41b6);
      puVar3 = puVar3 + 1 + uVar1;
      *(int *)0x41b6 = *(int *)0x41b6 + uVar1;
      FUN_1000_6326();
      param_2 = uVar2 - uVar1;
    }
  }
  return;
}


// ---- FUN_1000_65e0 @ 1000:65e0 ----

void __cdecl16near FUN_1000_65e0(undefined2 param_1,undefined2 param_2,uint param_3)

{
  uint uVar1;
  undefined2 unaff_DS;
  
  for (; param_3 != 0; param_3 = param_3 - uVar1) {
    uVar1 = *(int *)0x41b4 - *(int *)0x41b6;
    if (param_3 <= (uint)(*(int *)0x41b4 - *(int *)0x41b6)) {
      uVar1 = param_3;
    }
    FUN_1000_6053(*(undefined2 *)0x41b6);
    *(int *)0x41b6 = *(int *)0x41b6 + uVar1;
    FUN_1000_633d();
  }
  return;
}


// ---- FUN_1000_661f @ 1000:661f ----

void __cdecl16near FUN_1000_661f(undefined1 *param_1,int param_2)

{
  undefined1 *puVar1;
  int iVar2;
  undefined1 *puVar3;
  undefined2 uVar4;
  
  uVar4 = (undefined2)((ulong)param_1 >> 0x10);
  puVar3 = (undefined1 *)param_1;
  for (; param_2 != 0; param_2 = param_2 + -1) {
    iVar2 = FUN_1000_6490();
    *puVar3 = (char)iVar2;
    if (iVar2 == 0) break;
    puVar3 = puVar3 + 1;
  }
  for (; param_2 != 0; param_2 = param_2 + -1) {
    puVar1 = puVar3;
    puVar3 = puVar3 + 1;
    *puVar1 = 0x20;
  }
  return;
}


// ---- FUN_1000_6645 @ 1000:6645 ----

void __cdecl16near FUN_1000_6645(undefined4 param_1,int param_2)

{
  int iVar1;
  char *pcVar2;
  undefined2 uVar3;
  
  uVar3 = (undefined2)((ulong)param_1 >> 0x10);
  pcVar2 = (char *)((int)param_1 + param_2);
  iVar1 = param_2;
  do {
    pcVar2 = pcVar2 + -1;
    if (*pcVar2 != ' ') break;
    iVar1 = iVar1 + -1;
  } while (iVar1 != 0);
  FUN_1000_65e0((int)param_1,uVar3,iVar1);
  if (iVar1 != param_2) {
    FUN_1000_6499(0);
  }
  return;
}


// ---- FUN_1000_6679 @ 1000:6679 ----

void __cdecl16near FUN_1000_6679(void)

{
  undefined2 unaff_DS;
  
  if (*(int *)0x41ae != 8) {
    FUN_1000_64ff(*(undefined2 *)0x41ae);
  }
  return;
}


// ---- FUN_1000_669c @ 1000:669c ----

uint __cdecl16near FUN_1000_669c(char *param_1,int param_2,uint param_3)

{
  undefined2 unaff_DS;
  
  for (; param_2 != 0; param_2 = param_2 + -1) {
    param_3 = CONCAT11((char)(param_3 >> 8),(char)param_3 + *param_1) << 1 |
              (uint)((int)param_3 < 0);
    param_1 = param_1 + 1;
  }
  return param_3;
}


// ---- FUN_1000_66e6 @ 1000:66e6 ----

void __cdecl16near FUN_1000_66e6(undefined1 *param_1,int param_2)

{
  undefined1 *puVar1;
  undefined1 *puVar2;
  undefined1 uVar3;
  int iVar4;
  uint uVar5;
  undefined1 *puVar6;
  undefined1 *puVar7;
  undefined1 *puVar8;
  undefined2 uVar9;
  
  uVar9 = (undefined2)((ulong)param_1 >> 0x10);
  puVar7 = (undefined1 *)param_1;
  puVar1 = puVar7 + param_2;
  uRam00016729 = FUN_1000_6490();
                    /* WARNING: Read-only address (ram,0x00016729) is written */
  bRam0001671f = FUN_1000_6490();
                    /* WARNING: Read-only address (ram,0x0001671f) is written */
  iRam00016751 = 1 << (bRam0001671f & 0x1f);
                    /* WARNING: Read-only address (ram,0x00016751) is written */
  uRam0001674c = FUN_1000_6490();
                    /* WARNING: Read-only address (ram,0x0001674c) is written */
  while (puVar7 < puVar1) {
    iVar4 = FUN_1000_64ab();
    if (iVar4 == 0) {
      iVar4 = FUN_1000_64ff(0);
LAB_1000_6723:
      puVar6 = puVar7 + (-2 - iVar4);
      iVar4 = FUN_1000_64ff(0);
      uVar5 = iVar4 + 1;
      if ((uint)((int)puVar1 - (int)puVar7) <= uVar5) break;
      do {
        puVar8 = puVar7;
        puVar2 = puVar6;
        puVar6 = puVar6 + 1;
        *puVar8 = *puVar2;
        uVar5 = uVar5 - 1;
        puVar7 = puVar8 + 1;
      } while (uVar5 != 0);
      puVar7 = puVar8 + 2;
      puVar8[1] = *puVar6;
    }
    else {
      iVar4 = FUN_1000_64ab();
      if (iVar4 == 0) {
        iVar4 = FUN_1000_64ff(0);
        iVar4 = iVar4 + -0xf10;
        goto LAB_1000_6723;
      }
      uVar3 = FUN_1000_64ff(8);
      puVar2 = puVar7;
      puVar7 = puVar7 + 1;
      *puVar2 = uVar3;
    }
  }
  FUN_1000_6679();
  return;
}


