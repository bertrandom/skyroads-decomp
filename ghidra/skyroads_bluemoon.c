// Decompiled from SKYROADS.EXE by Ghidra

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
  *(undefined1 **)0x3194 = &stack0xfffe;
  *(undefined2 *)0x3196 = unaff_ES;
  pcVar1 = (code *)swi(0x10);
  (*pcVar1)();
  *(undefined1 **)0x3198 = &stack0xfffe;
  *(undefined2 *)0x319a = unaff_ES;
  return;
}


// ---- FUN_1000_0046 @ 1000:0046 ----

void __cdecl16near FUN_1000_0046(void)

{
  FUN_1000_5fdf(3);
  FUN_1000_3b4f();
  FUN_1000_5889();
  FUN_1000_5ba4();
  FUN_1000_5fc3(0);
  return;
}


// ---- FUN_1000_0069 @ 1000:0069 ----

void __cdecl16near FUN_1000_0069(void)

{
  undefined2 unaff_DS;
  
  if (*(int *)0x41b6 != 0) {
    FUN_1000_5fdf(3);
    FUN_1000_3b4f();
    FUN_1000_5889();
    if (*(int *)0x41b6 == 8) {
      FUN_1000_5c43(0xcce);
    }
    else {
      FUN_1000_5c43(0xce0);
      FUN_1000_61ec(*(undefined2 *)0x41b6,0);
    }
    FUN_1000_60ab();
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
  
  uVar1 = FUN_1000_5c38(0xd08);
  FUN_1000_639a(uVar1,0,0x1000,0);
  *(undefined2 *)0x54b4 = 0;
  while (*(int *)0x41b6 == 0) {
    iVar2 = FUN_1000_64f0();
    iVar3 = FUN_1000_64f0();
    if (*(int *)0x41b6 == 0) {
      if (*(int *)0x456c == 0) {
        uVar4 = FUN_1000_3ed8(0x7d64,0);
        *(undefined2 *)0x456c = uVar4;
        if ((*(int *)0x456c + 0x7d7U & 0xf000) != (*(uint *)0x456c & 0xf000)) {
          FUN_1000_3f56();
          *(undefined2 *)0x456c = 0;
        }
      }
      uVar5 = FUN_1000_3ed8(iVar2,0);
      *(uint *)(*(int *)0x54b4 * 2 + 0xe82) = uVar5;
      local_6 = (int *)((ulong)uVar5 << 0x10);
      *local_6 = iVar2 - iVar3;
      if (*(int *)0x41b6 == 0) {
        FUN_1000_6660(iVar2 - iVar3,uVar5,iVar3);
      }
    }
    *(int *)0x54b4 = *(int *)0x54b4 + 1;
  }
  FUN_1000_5bf5();
  FUN_1000_5c1a(uVar1);
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
  iVar3 = FUN_1000_5ffd();
  if (iVar3 == 0) {
    *(undefined2 *)0x36 = 0;
    iVar3 = FUN_1000_5fe9();
    if (iVar3 == 0) {
      FUN_1000_5c43(0xd14);
      return;
    }
  }
  FUN_1000_5a7c();
  FUN_1000_58b1();
  FUN_1000_3ab0();
  *(undefined2 *)0x457e = 1;
  FUN_1000_0000();
  FUN_1000_571b();
  FUN_1000_57a8(0);
  FUN_1000_54ec();
  FUN_1000_00bb();
  FUN_1000_0069();
  FUN_1000_2cb2();
LAB_1000_0219:
  bVar2 = true;
  iVar3 = FUN_1000_4575();
  if (iVar3 == 0) {
    *(undefined2 *)0x9602 = 3;
    goto LAB_1000_0251;
  }
LAB_1000_0232:
  *(undefined2 *)0x9602 = *(undefined2 *)0x4526;
  FUN_1000_4e36(!bVar2);
LAB_1000_0251:
  bVar2 = false;
  FUN_1000_3f04();
  FUN_1000_554b();
  do {
    FUN_1000_3f04();
    if (*(int *)0x9602 == 3) {
      uVar5 = FUN_1000_55f8(0);
      *(undefined2 *)0x41ce = uVar5;
      FUN_1000_536b(0);
    }
    else {
      iVar3 = FUN_1000_5164();
      if (iVar3 != 0) {
        FUN_1000_3f1f();
        FUN_1000_3f1f();
        goto LAB_1000_0232;
      }
      *(undefined2 *)0x9602 = *(undefined2 *)0x4526;
      uVar4 = FUN_1000_019c();
      uVar4 = uVar4 % 0xc;
      if (uVar4 == local_8) {
        uVar4 = (uVar4 + 1) % 0xc;
      }
      FUN_1000_57a8(uVar4 + 2);
      uVar5 = FUN_1000_55f8(*(int *)0x933e + 1);
      *(undefined2 *)0x41ce = uVar5;
      FUN_1000_536b(*(uint *)0x933e / 3);
      local_8 = uVar4;
    }
    if (*(int *)0x36 != 0) {
      uVar5 = FUN_1000_3ed8(0xac80,0);
      *(undefined2 *)0x5486 = uVar5;
    }
    FUN_1000_0069();
    FUN_1000_0707();
    iVar3 = 0;
    for (uVar4 = 0; uVar4 < 0x1e; uVar4 = uVar4 + 1) {
      if (*(int *)(uVar4 * 2 + 0x452a) != 0) {
        iVar3 = iVar3 + 1;
      }
    }
    do {
      FUN_1000_4137();
      if ((*(int *)(*(int *)0x933e * 2 + 0x452a) == 0) && (iVar3 == 0x1d)) {
        uVar5 = 1;
      }
      else {
        uVar5 = 0;
      }
      iVar6 = FUN_1000_2b21(uVar5);
      if (*(int *)0x9602 == 3) {
        FUN_1000_3f1f();
        FUN_1000_3f1f();
        if (iVar6 != 7) goto LAB_1000_0219;
        goto LAB_1000_0232;
      }
      if (iVar6 == 0) {
        piVar1 = (int *)(*(int *)0x933e * 2 + 0x452a);
        *piVar1 = *piVar1 + 1;
        *(int *)0x933e = *(int *)0x933e + 1;
        FUN_1000_5770();
      }
    } while ((iVar6 != 7) && (iVar6 != 0));
    FUN_1000_3f1f();
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
  
  *(undefined2 *)0xaf48 = *(undefined2 *)0x160c;
  if (*(int *)0x4528 == 0) {
    if (*(int *)0xcc2 == 0) {
      bVar5 = in(0x61);
      out(0x61,bVar5 | 3);
      *(undefined2 *)0xba0 = *(undefined2 *)(param_1 * 2 + 0x132);
    }
    else {
      uVar1 = *(undefined2 *)0x456c;
      iVar2 = *(int *)((param_1 + 1) * 2);
      iVar3 = *(int *)(param_1 * 2);
      puVar4 = (undefined1 *)*(undefined2 *)(param_1 * 2);
      local_8 = (undefined1 *)CONCAT22(uVar1,puVar4);
      FUN_1000_5ba4();
      FUN_1000_5b5a(puVar4 + 1,uVar1,*local_8,(iVar2 - iVar3) + -1);
    }
  }
  return;
}


// ---- FUN_1000_0476 @ 1000:0476 ----

bool __cdecl16near FUN_1000_0476(void)

{
  undefined2 unaff_DS;
  bool bVar1;
  
  if (*(int *)0xcc2 == 0) {
    bVar1 = *(int *)*(undefined2 *)0xba0 != 0;
  }
  else {
    bVar1 = *(uint *)0x160c < *(int *)0xaf48 + 8U;
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
    uVar4 = FUN_1000_5d4e(param_1,param_2,0x2000,0);
    uVar4 = FUN_1000_5d4e(uVar4,8,0);
    iVar2 = FUN_1000_5d0e(uVar4,0xe,0);
    uVar3 = *(undefined2 *)(iVar2 + 0x1638 + (uVar1 / 0x2e) * 2);
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
             (uint)(*(int *)(local_6 * 2 + 0x92) + *(int *)(local_6 * 2 + 0x46)) / 2;
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
    return *(int *)0x5180;
  }
  return *(int *)0x548a;
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
  
  if (*(int *)0x9602 == 1) {
    uVar1 = FUN_1000_05f6(1);
    *(undefined2 *)0x5180 = uVar1;
    uVar1 = FUN_1000_05f6(2);
    *(undefined2 *)0x548a = uVar1;
  }
  else if (*(int *)0x9602 == 2) {
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
  
  iVar4 = *(int *)0x9602;
  if (iVar4 == 0) {
    *(int *)0x9600 =
         (uint)(((*(byte *)0xba5 & 0x80) != 0 || (*(byte *)0xba7 & 0x80) != 0) ||
               (*(byte *)0xba9 & 0x80) != 0) -
         (uint)(((*(byte *)0xba4 & 0x80) != 0 || (*(byte *)0xba6 & 0x80) != 0) ||
               (*(byte *)0xba8 & 0x80) != 0);
    *(int *)0x933c =
         (uint)(((*(byte *)0xba2 & 0x80) != 0 || (*(byte *)0xba6 & 0x80) != 0) ||
               (*(byte *)0xba7 & 0x80) != 0) -
         (uint)(((*(byte *)0xba3 & 0x80) != 0 || (*(byte *)0xba8 & 0x80) != 0) ||
               (*(byte *)0xba9 & 0x80) != 0);
    *(uint *)0x5488 = (uint)((*(byte *)0xbab & 0x80) != 0);
  }
  else if (iVar4 == 1) {
    uVar1 = FUN_1000_05f6(1);
    uVar2 = FUN_1000_05f6(2);
    *(int *)0x9600 =
         (uint)((uint)(((long)*(int *)0x5180 * 3 & 0xffffU) / 2) < uVar1) -
         (uint)(uVar1 < *(uint *)0x5180 / 2);
    *(int *)0x933c =
         (uint)(uVar2 < *(uint *)0x548a / 2) -
         (uint)((uint)(((long)*(int *)0x548a * 3 & 0xffffU) / 2) < uVar2);
    uVar3 = FUN_1000_0672();
    *(undefined2 *)0x5488 = uVar3;
  }
  else if (iVar4 == 2) {
    uVar1 = FUN_1000_06b9(0);
    uVar2 = FUN_1000_06b9(0);
    *(int *)0x9600 = (uint)(0xaa < uVar2) - (uint)(uVar1 < 0x96);
    uVar1 = FUN_1000_06b9(1);
    uVar2 = FUN_1000_06b9(1);
    *(int *)0x933c = (uint)(uVar2 < 0xf) - (uint)(0xb9 < uVar1);
    uVar3 = FUN_1000_06b9(2);
    *(undefined2 *)0x5488 = uVar3;
    uVar3 = FUN_1000_06b9(1);
    FUN_1000_06a4(0xa0,uVar3);
  }
  else if (iVar4 == 3) {
    iVar4 = FUN_1000_5d4e(*(undefined2 *)0x9628,*(undefined2 *)0x962a,0x666,0);
    *(int *)0x933c = (*(byte *)(iVar4 + -0x69d2) & 3) - 1;
    iVar4 = FUN_1000_5d4e(*(undefined2 *)0x9628,*(undefined2 *)0x962a,0x666,0);
    *(int *)0x9600 = (*(byte *)(iVar4 + -0x69d2) >> 2 & 3) - 1;
    iVar4 = FUN_1000_5d4e(*(undefined2 *)0x9628,*(undefined2 *)0x962a,0x666,0);
    *(uint *)0x5488 = *(byte *)(iVar4 + -0x69d2) >> 4 & 1;
  }
  return;
}


// ---- FUN_1000_0afa @ 1000:0afa ----

undefined2 __cdecl16near FUN_1000_0afa(int param_1,uint param_2)

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


// ---- FUN_1000_0b34 @ 1000:0b34 ----

int __cdecl16near FUN_1000_0b34(uint param_1)

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


// ---- FUN_1000_0b71 @ 1000:0b71 ----

undefined2 __cdecl16near
FUN_1000_0b71(undefined2 param_1,undefined2 param_2,undefined2 param_3,int param_4)

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
    uVar3 = *(undefined2 *)((uVar2 >> 8) * 2 + 0xde);
  }
  return uVar3;
}


// ---- FUN_1000_0be3 @ 1000:0be3 ----

void __cdecl16near FUN_1000_0be3(int param_1)

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
  
  iVar1 = FUN_1000_0533(*(undefined2 *)0x9628,*(undefined2 *)0x962a,*(undefined2 *)0xaf2c,
                        *(undefined2 *)0xaf3c);
  if (*(int *)0x4578 == 0) {
    if (*(int *)0x457c == 4) {
      iVar8 = 0;
    }
    else {
      iVar8 = *(int *)((int)(((ulong)*(uint *)0x160c / 2) % 4) * 2 + 0xea);
    }
    if (iVar1 == 0) {
      iVar2 = FUN_1000_0afa(*(undefined2 *)0x9342,*(undefined2 *)0xaf3c);
    }
    else {
      iVar2 = 0;
    }
    iVar3 = FUN_1000_0b34(*(undefined2 *)0xaf2c);
    uVar4 = (iVar3 * 3 + iVar2) * 3 + 0xe + iVar8;
  }
  else {
    uVar4 = *(uint *)0x4578 / 3;
    if (0xd < uVar4) {
      uVar4 = 0xffff;
    }
  }
  uVar5 = FUN_1000_0b71(*(undefined2 *)0x9628,*(undefined2 *)0x962a,*(int *)0xaf2c + -0x380,iVar1);
  uVar6 = FUN_1000_0b71(*(undefined2 *)0x9628,*(undefined2 *)0x962a,*(int *)0xaf2c + 0x380,iVar1);
  if ((((*(int *)0xe28 != *(int *)0x9628) || (*(int *)0xe2a != *(int *)0x962a)) ||
      (*(int *)0xe2c != *(int *)0xaf2c)) ||
     (((*(int *)0xe2e != *(int *)0xaf3c || (*(uint *)0xe30 != uVar4)) ||
      (*(int *)0xe32 != *(int *)0x9340)))) {
    uVar10 = *(undefined2 *)0x962a;
    *(undefined2 *)0xe28 = *(undefined2 *)0x9628;
    *(undefined2 *)0xe2a = uVar10;
    *(undefined2 *)0xe2c = *(undefined2 *)0xaf2c;
    if (param_1 == 0) {
      iVar1 = *(int *)0xaf3c;
    }
    else {
      iVar1 = *(int *)0xaf3c + -0x80;
    }
    *(int *)0xe2e = iVar1;
    *(uint *)0xe30 = uVar4;
    *(undefined2 *)0xe32 = *(undefined2 *)0x9340;
    if (*(int *)0x36 == 0) {
      iVar1 = (uint)(*(int *)0x9340 == 0) * 0x200 + -0x6000;
    }
    else {
      iVar1 = *(int *)0x5486;
    }
    if (*(int *)0x4578 == 0) {
      if (uVar5 < uVar6) {
        uVar5 = uVar6;
      }
      uVar5 = (*(int *)0xaf3c - uVar5) / 0x80;
    }
    else {
      uVar5 = 0x7fff;
    }
    uVar10 = *(undefined2 *)0x4570;
    uVar9 = *(undefined2 *)0xaf46;
    iVar8 = *(int *)0xaf44 + uVar4 * 0x2d0;
    if (uVar4 == 0xffff) {
      uVar4 = 0;
    }
    else {
      uVar4 = *(uint *)0xe2e / 0x80;
    }
    uVar7 = FUN_1000_5d4e(*(undefined2 *)0x9628,*(undefined2 *)0x962a,0x2000,0);
    iVar1 = FUN_1000_0b34(*(undefined2 *)0xaf2c,uVar7,uVar4,iVar8,uVar9,uVar10,uVar5,iVar1);
    FUN_1000_2d03(*(uint *)0xaf2c / 0x80 + *(int *)(iVar1 * 2 + 0x38));
    *(uint *)0x9340 = *(uint *)0x9340 ^ 1;
    *(undefined2 *)0x4570 = 0;
  }
  return;
}


// ---- FUN_1000_0e23 @ 1000:0e23 ----

void __cdecl16near FUN_1000_0e23(void)

{
  code *pcVar1;
  undefined2 unaff_DS;
  
  if (*(int *)0x36 == 0) {
    pcVar1 = (code *)swi(0x10);
    (*pcVar1)();
  }
  return;
}


// ---- FUN_1000_0e3e @ 1000:0e3e ----

void __cdecl16near FUN_1000_0e3e(void)

{
  undefined2 unaff_DS;
  
  do {
  } while (*(int *)0x160c == *(int *)0x160c);
  return;
}


// ---- FUN_1000_0e58 @ 1000:0e58 ----

undefined2 __cdecl16near FUN_1000_0e58(void)

{
  uint *puVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  undefined2 unaff_DS;
  
  *(undefined2 *)0xaf3c = 0;
  *(undefined2 *)0x160c = 0;
  while( true ) {
    if (0x47 < *(uint *)0x160c) {
      return 0;
    }
    if ((*(byte *)0xbaa & 0x80) != 0) break;
    FUN_1000_0be3(0);
    FUN_1000_0e3e();
    FUN_1000_0e23();
    uVar3 = *(uint *)0x54b8;
    iVar4 = *(int *)0x54ba;
    puVar1 = (uint *)0x9628;
    uVar2 = *puVar1;
    *puVar1 = *puVar1 + uVar3;
    *(int *)0x962a = *(int *)0x962a + iVar4 + (uint)CARRY2(uVar2,uVar3);
  }
  return 7;
}


// ---- FUN_1000_0eb5 @ 1000:0eb5 ----

void __cdecl16near FUN_1000_0eb5(char *param_1,int param_2,undefined1 param_3,undefined1 param_4)

{
  char *pcVar1;
  undefined1 *puVar2;
  undefined2 uVar3;
  undefined1 uVar4;
  char *pcVar5;
  undefined1 *puVar6;
  undefined2 unaff_DS;
  
  uVar3 = *(undefined2 *)0xaf3a;
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


// ---- FUN_1000_0edf @ 1000:0edf ----

void __cdecl16near FUN_1000_0edf(undefined2 *param_1,int param_2)

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
  
  if (*(int *)0x36 == 0) {
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
  local_10 = *(undefined2 *)0xaf3a;
  local_e = *param_1;
  uVar4 = (undefined2)((ulong)param_1 >> 0x10);
  puVar2 = (undefined2 *)param_1;
  local_a = (uint)*(byte *)(puVar2 + 1);
  local_c = (uint)*(byte *)((int)puVar2 + 3);
  local_8 = local_a * local_c;
  FUN_1000_0eb5(puVar2 + 2,uVar4,local_8,uVar3,uVar1);
  if (*(int *)0x36 == 0) {
    FUN_1000_3c7e();
  }
  FUN_1000_4162(0,0xa000,0,1);
  FUN_1000_41e5(&local_10);
  if (*(int *)0x36 == 0) {
    FUN_1000_4162(0,0xa200,0,1);
    FUN_1000_41e5(&local_10);
  }
  return;
}


// ---- FUN_1000_0fc6 @ 1000:0fc6 ----

void __cdecl16near
FUN_1000_0fc6(int param_1,int param_2,undefined2 param_3,undefined2 param_4,undefined2 param_5)

{
  undefined2 unaff_DS;
  undefined2 local_e;
  int local_c;
  undefined2 local_a;
  undefined2 local_8;
  
  FUN_1000_0eb5(param_5);
  local_e = *(undefined2 *)0xaf3a;
  local_c = param_2 * 0x140 + param_1;
  local_8 = param_3;
  local_a = param_4;
  if (*(int *)0x36 == 0) {
    FUN_1000_3c7e();
  }
  FUN_1000_4162(0,0xa000,0,0);
  FUN_1000_41e5(&local_e);
  if (*(int *)0x36 == 0) {
    FUN_1000_4162(0,0xa200,0,0);
    FUN_1000_41e5(&local_e);
  }
  return;
}


// ---- FUN_1000_1067 @ 1000:1067 ----

void __cdecl16near FUN_1000_1067(int param_1,undefined2 param_2,uint param_3,uint param_4)

{
  int iVar1;
  uint uVar2;
  undefined2 unaff_DS;
  
  for (uVar2 = 0; (uVar2 < param_4 && ((param_3 != 0 || (uVar2 == 0)))); uVar2 = uVar2 + 1) {
    iVar1 = (int)(((ulong)param_3 / (ulong)*(uint *)(uVar2 * 2 + 0x308)) % 10);
    FUN_1000_0fc6(((param_4 - uVar2) + -1) * 5 + param_1,param_2,4,5,iVar1 * 0x14 + 0x13c);
    param_3 = param_3 - iVar1 * *(int *)(uVar2 * 2 + 0x308);
  }
  return;
}


// ---- FUN_1000_10e4 @ 1000:10e4 ----

uint __cdecl16near FUN_1000_10e4(int param_1,int param_2)

{
  uint uVar1;
  undefined2 unaff_DS;
  
  if (*(int *)0x36 == 0) {
    uVar1 = FUN_1000_3e30(param_1,param_2);
  }
  else {
    uVar1 = (uint)*(byte *)(param_2 * 0x140 + param_1);
  }
  return uVar1;
}


// ---- FUN_1000_1126 @ 1000:1126 ----

void __cdecl16near FUN_1000_1126(int param_1,int param_2,undefined2 param_3)

{
  undefined2 unaff_DS;
  
  if (*(int *)0x36 == 0) {
    FUN_1000_3df3(param_1,param_2,param_3);
  }
  else {
    *(undefined1 *)(param_2 * 0x140 + param_1) = (char)param_3;
  }
  return;
}


// ---- FUN_1000_116b @ 1000:116b ----

void __cdecl16near FUN_1000_116b(int param_1)

{
  int iVar1;
  int iVar2;
  undefined2 uVar3;
  int iVar4;
  undefined2 unaff_DS;
  
  param_1 = param_1 + 0x2a;
  iVar4 = 0x8f;
  iVar1 = FUN_1000_10e4(param_1,0x8f);
  while (iVar2 = FUN_1000_10e4(param_1,iVar4), iVar2 == iVar1) {
    iVar4 = iVar4 + -1;
  }
  while( true ) {
    iVar4 = iVar4 + 1;
    iVar2 = FUN_1000_10e4(param_1,iVar4);
    if (iVar2 != iVar1) break;
    if (*(int *)0x36 == 0) {
      uVar3 = 6;
    }
    else {
      uVar3 = 0x60;
    }
    FUN_1000_1126(param_1,iVar4,uVar3);
  }
  return;
}


// ---- FUN_1000_11d5 @ 1000:11d5 ----

void __cdecl16near
FUN_1000_11d5(uint param_1,uint param_2,int param_3,int param_4,int param_5,int param_6)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  
  for (uVar2 = param_1; uVar3 = param_2, uVar2 < param_1 + param_3; uVar2 = uVar2 + 1) {
    for (; uVar3 < param_2 + param_4; uVar3 = uVar3 + 1) {
      iVar1 = FUN_1000_10e4(uVar2,uVar3);
      if (iVar1 == param_5) {
        FUN_1000_1126(uVar2,uVar3,param_6);
      }
      else if (iVar1 == param_6) {
        FUN_1000_1126(uVar2,uVar3,param_5);
      }
    }
  }
  return;
}


// ---- FUN_1000_124b @ 1000:124b ----

void __cdecl16near FUN_1000_124b(void)

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
  
  uVar2 = (uint)(4 < *(uint *)0x160c % 9);
  local_8 = FUN_1000_5e1c(*(uint *)0x54b8 - *(uint *)0xaf3e,
                          (*(int *)0x54ba - *(int *)0xaf40) -
                          (uint)(*(uint *)0x54b8 < *(uint *)0xaf3e),0x141,0);
  if (0x22 < local_8) {
    local_8 = 0x22;
  }
  uVar6 = local_8;
  if (*(uint *)0x41ca < local_8) {
    uVar6 = *(uint *)0x41ca;
  }
  while( true ) {
    uVar3 = local_8;
    if (local_8 < *(uint *)0x41ca) {
      uVar3 = *(uint *)0x41ca;
    }
    if (uVar3 <= uVar6) break;
    FUN_1000_0edf(*(int *)0x54b0 + *(int *)(uVar6 * 2 + 0x4580),*(undefined2 *)0x54b2,
                  *(uint *)0x41ca < local_8);
    uVar6 = uVar6 + 1;
  }
  *(uint *)0x41ca = local_8;
  local_a = (*(int *)0xb14c + 2999U) / 3000;
  if (10 < local_a) {
    local_a = 10;
  }
  uVar6 = local_a;
  if (*(uint *)0x457a < local_a) {
    uVar6 = *(uint *)0x457a;
  }
  while( true ) {
    uVar3 = local_a;
    if (local_a < *(uint *)0x457a) {
      uVar3 = *(uint *)0x457a;
    }
    if (uVar3 <= uVar6) break;
    FUN_1000_0edf(*(int *)0x5482 + *(int *)(uVar6 * 2 + -0x69fc),*(undefined2 *)0x5484,
                  *(uint *)0x457a < local_a);
    uVar6 = uVar6 + 1;
  }
  *(uint *)0x457a = local_a;
  if ((*(int *)0x457c == 5) && (uVar2 != *(uint *)0xaf2e)) {
    if (*(int *)0x36 == 0) {
      uVar4 = 4;
    }
    else {
      uVar4 = 100;
    }
    if (*(int *)0x36 == 0) {
      uVar5 = 0xf;
    }
    else {
      uVar5 = 99;
    }
    FUN_1000_11d5(0xa0,0xa1,7,7,uVar5,uVar4);
    if (uVar2 != 0) {
      FUN_1000_03c2(3);
    }
  }
  local_c = (*(int *)0x54a0 + 2999U) / 3000;
  if (10 < local_c) {
    local_c = 10;
  }
  uVar6 = local_c;
  if (*(uint *)0x9618 < local_c) {
    uVar6 = *(uint *)0x9618;
  }
  while( true ) {
    uVar3 = local_c;
    if (local_c < *(uint *)0x9618) {
      uVar3 = *(uint *)0x9618;
    }
    if (uVar3 <= uVar6) break;
    FUN_1000_0edf(*(int *)0x961a + *(int *)(uVar6 * 2 + 0x548c),*(undefined2 *)0x961c,
                  *(uint *)0x9618 < local_c);
    uVar6 = uVar6 + 1;
  }
  *(uint *)0x9618 = local_c;
  if ((*(int *)0x457c == 4) && (uVar2 != *(uint *)0xaf2e)) {
    if (*(int *)0x36 == 0) {
      uVar4 = 4;
    }
    else {
      uVar4 = 100;
    }
    if (*(int *)0x36 == 0) {
      uVar5 = 0xf;
    }
    else {
      uVar5 = 99;
    }
    FUN_1000_11d5(0x9b,0xa9,0x10,5,uVar5,uVar4);
    if (uVar2 != 0) {
      FUN_1000_03c2(3);
    }
  }
  uVar4 = *(undefined2 *)0x9628;
  iVar1 = *(int *)0x962a;
  uVar7 = FUN_1000_5d42();
  uVar7 = FUN_1000_5e1c((int)uVar7,(int)((ulong)uVar7 >> 0x10) + -3,0x1e,0);
  local_e = FUN_1000_5d4e(uVar4,iVar1 + -3,uVar7);
  if (0x1d < local_e) {
    local_e = 0x1d;
  }
  for (uVar6 = *(uint *)0x456a; uVar6 < local_e; uVar6 = uVar6 + 1) {
    FUN_1000_116b(uVar6);
  }
  *(uint *)0x456a = local_e;
  if (*(int *)0xaf30 != *(int *)0x4568) {
    FUN_1000_0fc6(0xcb,0x9c,0x1a,5,*(int *)0x4568 * 0x82 + 0x204);
  }
  *(undefined2 *)0xaf30 = *(undefined2 *)0x4568;
  *(uint *)0xaf2e = uVar2;
  return;
}


// ---- FUN_1000_1584 @ 1000:1584 ----

uint __cdecl16near FUN_1000_1584(uint param_1,uint param_2,uint param_3)

{
  uint uVar1;
  undefined2 unaff_DS;
  
  if (param_2 < 0x26) {
    uVar1 = (param_3 + 0xde00) / 0x80;
    param_1 = param_1 & 0xf00;
    if (param_1 == 0x100) {
      if ((uVar1 < *(uint *)(param_2 * 2 + 0x92)) && (*(uint *)(param_2 * 2 + 0x46) <= uVar1)) {
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
      if ((param_3 < 0x3200) && (*(uint *)(param_2 * 2 + 0x46) <= uVar1)) {
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
      if ((param_3 < 0x3c00) && (*(uint *)(param_2 * 2 + 0x46) <= uVar1)) {
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


// ---- FUN_1000_1685 @ 1000:1685 ----

undefined2 __cdecl16near
FUN_1000_1685(undefined2 param_1,undefined2 param_2,uint param_3,uint param_4)

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
LAB_1000_17b4:
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
    iVar3 = FUN_1000_1584(uVar4,local_a,param_4);
    if (iVar3 == 0) {
      uVar4 = FUN_1000_04c0(param_1,param_2,param_3 + local_c,0x2f - local_a,param_4);
      iVar3 = FUN_1000_1584(uVar4);
      if (iVar3 == 0) goto LAB_1000_17b4;
    }
    uVar4 = 1;
  }
  return uVar4;
}


// ---- FUN_1000_17be @ 1000:17be ----

/* WARNING: Removing unreachable block (ram,0x0001190d) */

void __cdecl16near FUN_1000_17be(uint param_1,int param_2,uint param_3,uint param_4)

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
  
  if ((((*(uint *)0x9628 != param_1) || (*(int *)0x962a != param_2)) || (*(uint *)0xaf2c != param_3)
      ) || (*(uint *)0xaf3c != param_4)) {
    for (uVar6 = 1; uVar6 < 6; uVar6 = uVar6 + 1) {
      iVar3 = (int)((param_4 - *(int *)0xaf3c) * uVar6) / 5 + *(int *)0xaf3c;
      iVar4 = (int)((param_3 - *(int *)0xaf2c) * uVar6) / 5 + *(int *)0xaf2c;
      uVar7 = FUN_1000_5d0e(param_1 - *(uint *)0x9628,
                            (param_2 - *(int *)0x962a) - (uint)(param_1 < *(uint *)0x9628),uVar6,0);
      uVar7 = FUN_1000_5e1c(uVar7,5,0);
      iVar3 = FUN_1000_1685((uint)uVar7 + *(uint *)0x9628,
                            (int)((ulong)uVar7 >> 0x10) + *(int *)0x962a +
                            (uint)CARRY2((uint)uVar7,*(uint *)0x9628),iVar4,iVar3);
      if (iVar3 != 0) break;
    }
    uVar7 = FUN_1000_5d0e(param_1 - *(uint *)0x9628,
                          (param_2 - *(int *)0x962a) - (uint)(param_1 < *(uint *)0x9628),uVar6 - 1,0
                         );
    uVar7 = FUN_1000_5e1c(uVar7,5,0);
    puVar1 = (uint *)0x9628;
    uVar2 = *puVar1;
    *puVar1 = *puVar1 + (uint)uVar7;
    *(int *)0x962a = *(int *)0x962a + (int)((ulong)uVar7 >> 0x10) + (uint)CARRY2(uVar2,(uint)uVar7);
    *(int *)0xaf2c = *(int *)0xaf2c + (int)((param_3 - *(int *)0xaf2c) * (uVar6 - 1)) / 5;
    *(int *)0xaf3c = *(int *)0xaf3c + (int)((param_4 - *(int *)0xaf3c) * (uVar6 - 1)) / 5;
    uVar8 = 0x1000;
    while( true ) {
      local_8 = (int)(uVar8 >> 0x10);
      local_a = (uint)uVar8;
      if (uVar8 == 0) break;
      while ((uVar8 <= CONCAT22((param_2 - *(int *)0x962a) - (uint)(param_1 < *(uint *)0x9628),
                                param_1 - *(uint *)0x9628) &&
             (iVar3 = FUN_1000_1685(uVar8 + CONCAT22(*(undefined2 *)0x962a,*(undefined2 *)0x9628),
                                    *(undefined2 *)0xaf2c,*(undefined2 *)0xaf3c), iVar3 == 0))) {
        puVar1 = (uint *)0x9628;
        uVar6 = *puVar1;
        *puVar1 = *puVar1 + local_a;
        *(int *)0x962a = *(int *)0x962a + local_8 + (uint)CARRY2(uVar6,local_a);
      }
      uVar8 = FUN_1000_5d4e(uVar8,0x10,0);
    }
    if (*(uint *)0xaf2c < param_3) {
      iVar3 = 0x7d;
    }
    else {
      iVar3 = -0x7d;
    }
    for (; iVar3 != 0; iVar3 = iVar3 / 5) {
      while( true ) {
        if ((int)(param_3 - *(int *)0xaf2c) < 1) {
          iVar4 = -(param_3 - *(int *)0xaf2c);
        }
        else {
          iVar4 = param_3 - *(int *)0xaf2c;
        }
        iVar5 = iVar3;
        if (iVar3 < 1) {
          iVar5 = -iVar3;
        }
        if ((iVar4 < iVar5) ||
           (iVar4 = FUN_1000_1685(*(undefined2 *)0x9628,*(undefined2 *)0x962a,iVar3 + *(int *)0xaf2c
                                  ,*(undefined2 *)0xaf3c), iVar4 != 0)) break;
        *(int *)0xaf2c = *(int *)0xaf2c + iVar3;
      }
    }
    if (*(uint *)0xaf3c < param_4) {
      iVar3 = 0x7d;
    }
    else {
      iVar3 = -0x7d;
    }
    for (; iVar3 != 0; iVar3 = iVar3 / 5) {
      while( true ) {
        if ((int)(param_4 - *(int *)0xaf3c) < 1) {
          iVar4 = -(param_4 - *(int *)0xaf3c);
        }
        else {
          iVar4 = param_4 - *(int *)0xaf3c;
        }
        iVar5 = iVar3;
        if (iVar3 < 1) {
          iVar5 = -iVar3;
        }
        if ((iVar4 < iVar5) ||
           (iVar4 = FUN_1000_1685(*(undefined2 *)0x9628,*(undefined2 *)0x962a,*(undefined2 *)0xaf2c,
                                  iVar3 + *(int *)0xaf3c), iVar4 != 0)) break;
        *(int *)0xaf3c = *(int *)0xaf3c + iVar3;
      }
    }
  }
  return;
}


// ---- FUN_1000_1a9c @ 1000:1a9c ----

void __cdecl16near FUN_1000_1a9c(uint param_1)

{
  uint *puVar1;
  uint uVar2;
  undefined2 unaff_DS;
  
  param_1 = param_1 & 0xf;
  if (param_1 == 2) {
    if (*(int *)0x4578 == 0) {
      puVar1 = (uint *)0x54b8;
      uVar2 = *puVar1;
      *puVar1 = *puVar1 - 0x12f;
      *(int *)0x54ba = *(int *)0x54ba - (uint)(uVar2 < 0x12f);
    }
  }
  else if (param_1 == 9) {
    if (*(int *)0x457c == 0) {
      if ((*(uint *)0x54a0 < 27000) || (*(uint *)0xb14c < 27000)) {
        FUN_1000_03c2(4);
      }
      *(undefined2 *)0x54a0 = 30000;
      *(undefined2 *)0xb14c = 30000;
    }
  }
  else if (param_1 == 10) {
    if (*(int *)0x4578 == 0) {
      puVar1 = (uint *)0x54b8;
      uVar2 = *puVar1;
      *puVar1 = *puVar1 + 0x12f;
      *(int *)0x54ba = *(int *)0x54ba + (uint)(0xfed0 < uVar2);
    }
  }
  else if (param_1 == 0xc) {
    if (*(int *)0x457c == 0) {
      *(undefined2 *)0x457c = 2;
    }
    if (*(int *)0x4578 == 0) {
      *(undefined2 *)0x4578 = 1;
      FUN_1000_03c2(0);
    }
  }
  if ((*(int *)0x54ba < 1) && (*(int *)0x54ba < 0)) {
    *(undefined2 *)0x54b8 = 0;
    *(undefined2 *)0x54ba = 0;
  }
  else if ((-1 < *(int *)0x54ba) && ((0 < *(int *)0x54ba || (0x2aaa < *(uint *)0x54b8)))) {
    *(undefined2 *)0x54b8 = 0x2aaa;
    *(undefined2 *)0x54ba = 0;
  }
  return;
}


// ---- FUN_1000_1bb5 @ 1000:1bb5 ----

undefined2 __cdecl16near FUN_1000_1bb5(undefined2 param_1,undefined2 param_2,undefined2 param_3)

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


// ---- FUN_1000_1c20 @ 1000:1c20 ----

/* WARNING: Removing unreachable block (ram,0x00011cf1) */

undefined2 __cdecl16near
FUN_1000_1c20(undefined2 param_1,undefined2 param_2,uint param_3,uint param_4,undefined2 param_5,
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
    param_8 = param_8 + *(int *)0x54b6;
    lVar2 = lVar1 + lVar3;
    iVar5 = *(int *)0x54a2;
    uVar8 = FUN_1000_5d0e(lVar1 + 0x618,param_7,param_7 >> 0xf);
    iVar4 = FUN_1000_5e1c(uVar8,0x200,0);
    param_3 = uVar7 + iVar4 + iVar5;
    if ((param_3 < 0x2f80) || (0xd080 < param_3)) {
      return 0;
    }
    param_4 = param_4 + param_8;
    lVar9 = FUN_1000_5d0e(*(int *)0x933c,*(int *)0x933c >> 0xf,0x4b,0);
    lVar1 = lVar9 + lVar1;
    if ((lVar1 < 0x10000) && (lVar1 < 0)) {
      lVar1 = 0;
    }
    else if (0x2aaa < lVar1) {
      lVar1 = 0x2aaa;
    }
  } while (0x2800 < param_4);
  iVar5 = FUN_1000_1bb5(lVar3,uVar7);
  if ((iVar5 == 0) && (iVar5 = FUN_1000_1bb5(lVar2,param_3), iVar5 == 0)) {
    uVar6 = 1;
  }
  else {
    uVar6 = 0;
  }
  return uVar6;
}


// ---- FUN_1000_1d4d @ 1000:1d4d ----

void __cdecl16near FUN_1000_1d4d(void)

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
  
  iVar4 = FUN_1000_1c20(*(undefined2 *)0x9628,*(undefined2 *)0x962a,*(undefined2 *)0xaf2c,
                        *(undefined2 *)0xaf3c,*(undefined2 *)0x54b8,*(undefined2 *)0x54ba,
                        *(undefined2 *)0x4576,*(undefined2 *)0x9342);
  if (iVar4 == 0) {
    uVar1 = *(uint *)0x54b8;
    iVar4 = *(int *)0x54ba;
    iVar3 = *(int *)0x4576;
    for (iVar7 = 1; iVar7 < 7; iVar7 = iVar7 + 1) {
      uVar11 = *(undefined2 *)0x9342;
      iVar5 = (iVar3 * iVar7) / 10 + iVar3;
      *(int *)0x4576 = iVar5;
      iVar5 = FUN_1000_1c20(*(undefined2 *)0x9628,*(undefined2 *)0x962a,*(undefined2 *)0xaf2c,
                            *(undefined2 *)0xaf3c,*(undefined2 *)0x54b8,*(undefined2 *)0x54ba,iVar5,
                            uVar11);
      if (iVar5 != 0) break;
      uVar11 = *(undefined2 *)0x9342;
      iVar5 = iVar3 - (iVar3 * iVar7) / 10;
      *(int *)0x4576 = iVar5;
      iVar5 = FUN_1000_1c20(*(undefined2 *)0x9628,*(undefined2 *)0x962a,*(undefined2 *)0xaf2c,
                            *(undefined2 *)0xaf3c,*(undefined2 *)0x54b8,*(undefined2 *)0x54ba,iVar5,
                            uVar11);
      if (iVar5 != 0) break;
      *(int *)0x4576 = iVar3;
      uVar8 = FUN_1000_5d0e(uVar1,iVar4,iVar7,iVar7 >> 0xf);
      lVar9 = FUN_1000_5e1c(uVar8,10,0);
      lVar9 = lVar9 + CONCAT22(iVar4,uVar1);
      *(undefined2 *)0x54b8 = (int)lVar9;
      *(undefined2 *)0x54ba = (int)((ulong)lVar9 >> 0x10);
      if ((*(int *)0x54ba < 1) &&
         (((*(int *)0x54ba < 0 || (*(uint *)0x54b8 < 0x2aaa)) &&
          (iVar5 = FUN_1000_1c20(*(undefined2 *)0x9628,*(undefined2 *)0x962a,*(undefined2 *)0xaf2c,
                                 *(undefined2 *)0xaf3c,*(undefined2 *)0x54b8,*(undefined2 *)0x54ba,
                                 *(undefined2 *)0x4576,*(undefined2 *)0x9342), iVar5 != 0)))) break;
      uVar11 = *(undefined2 *)0x9342;
      uVar10 = *(undefined2 *)0x4576;
      uVar8 = FUN_1000_5d0e(uVar1,iVar4,iVar7,iVar7 >> 0xf);
      uVar8 = FUN_1000_5e1c(uVar8,10,0);
      iVar5 = uVar1 - (uint)uVar8;
      iVar6 = (iVar4 - (int)((ulong)uVar8 >> 0x10)) - (uint)(uVar1 < (uint)uVar8);
      *(int *)0x54b8 = iVar5;
      *(int *)0x54ba = iVar6;
      iVar5 = FUN_1000_1c20(*(undefined2 *)0x9628,*(undefined2 *)0x962a,*(undefined2 *)0xaf2c,
                            *(undefined2 *)0xaf3c,iVar5,iVar6,uVar10,uVar11);
      if (iVar5 != 0) break;
      *(uint *)0x54b8 = uVar1;
      *(int *)0x54ba = iVar4;
    }
    uVar2 = *(uint *)0x54b8;
    iVar3 = *(int *)0x54ba;
    *(int *)0xaf3e = uVar2 - uVar1;
    *(int *)0xaf40 = (iVar3 - iVar4) - (uint)(uVar2 < uVar1);
    if (iVar7 < 7) {
      *(undefined2 *)0x4568 = 1;
    }
  }
  return;
}


// ---- FUN_1000_1f2c @ 1000:1f2c ----

/* WARNING: Removing unreachable block (ram,0x000122d0) */

undefined2 __cdecl16near FUN_1000_1f2c(void)

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
  
  if (*(int *)0x9602 == 2) {
    FUN_1000_06a4(0xa0,100);
  }
  *(undefined2 *)0x517c = 0;
  uVar13 = FUN_1000_5d0e(*(undefined2 *)0x456e,0,0x1680,0);
  iVar6 = FUN_1000_5d4e(uVar13,400,0);
  *(int *)0x54b6 = -iVar6;
  *(undefined2 *)0x9628 = 0;
  *(undefined2 *)0x962a = 3;
  *(undefined2 *)0xaf2c = 0x8000;
  *(undefined2 *)0xaf3c = 0x2800;
  *(undefined2 *)0x54a2 = 0;
  *(undefined2 *)0x4576 = 0;
  *(undefined2 *)0x9342 = 0;
  *(undefined2 *)0x54b8 = 0;
  *(undefined2 *)0x54ba = 0;
  *(undefined2 *)0x54a0 = 30000;
  *(undefined2 *)0xb14c = 30000;
  *(undefined2 *)0x457c = 0;
  *(undefined2 *)0x4566 = 0;
  *(undefined2 *)0x4578 = 0;
  bVar3 = true;
  bVar12 = false;
  bVar11 = false;
  *(undefined2 *)0x4568 = 0;
  bVar5 = false;
  bVar4 = false;
  *(undefined2 *)0xaf3e = 0;
  *(undefined2 *)0xaf40 = 0;
  *(undefined2 *)0x160c = 0;
  local_4 = 0;
  *(undefined2 *)0x9620 = 0;
  *(undefined2 *)0x9622 = 0;
  *(undefined2 *)0xaf48 = 0;
  *(undefined2 *)0x4570 = 0;
  do {
    if (*(uint *)0x160c < local_4) {
      *(undefined2 *)0x160c = 0;
      local_4 = 0;
    }
    iVar6 = *(int *)0x160c;
    if ((*(byte *)0xbac & 0x80) != 0) {
      do {
      } while ((*(byte *)0xbac & 0x80) != 0);
      while ((((((*(byte *)0xba2 & 0x80) == 0 && ((*(byte *)0xba3 & 0x80) == 0)) &&
               ((*(byte *)0xba4 & 0x80) == 0)) &&
              (((*(byte *)0xba5 & 0x80) == 0 && ((*(byte *)0xba6 & 0x80) == 0)))) &&
             ((((*(byte *)0xba7 & 0x80) == 0 &&
               (((*(byte *)0xba8 & 0x80) == 0 && ((*(byte *)0xba9 & 0x80) == 0)))) &&
              ((*(byte *)0xbaa & 0x80) == 0))))) {
        if (((*(byte *)0xbab & 0x80) != 0) || ((*(byte *)0xbac & 0x80) != 0)) break;
      }
      if ((*(byte *)0xbaa & 0x80) != 0) {
        return 7;
      }
      do {
        do {
        } while ((*(byte *)0xba2 & 0x80) != 0);
      } while (((((((*(byte *)0xba3 & 0x80) != 0) || ((*(byte *)0xba4 & 0x80) != 0)) ||
                 ((*(byte *)0xba5 & 0x80) != 0)) ||
                ((((*(byte *)0xba6 & 0x80) != 0 || ((*(byte *)0xba7 & 0x80) != 0)) ||
                 (((*(byte *)0xba8 & 0x80) != 0 ||
                  (((*(byte *)0xba9 & 0x80) != 0 || ((*(byte *)0xbaa & 0x80) != 0)))))))) ||
               ((*(byte *)0xbab & 0x80) != 0)) || ((*(byte *)0xbac & 0x80) != 0));
      *(int *)0x160c = iVar6;
    }
    if ((*(byte *)0xbaa & 0x80) != 0) {
      return 7;
    }
    if (((*(int *)0x4578 == 0) || (0x2a < *(uint *)0x4578)) &&
       (((*(int *)0x457c == 1 || (*(int *)0x457c == 2)) ||
        (((*(int *)0x457c == 3 && (*(int *)0x4578 != 0)) || (0x6b < *(uint *)0x4566)))))) {
      return *(undefined2 *)0x457c;
    }
    FUN_1000_0be3(bVar12);
    FUN_1000_124b();
    do {
    } while (*(int *)0x160c == iVar6);
    FUN_1000_0e23();
    if (*(int *)0x36 == 0) {
      FUN_1000_5fc8();
    }
    if (*(int *)0x9602 != 3) {
      if (*(int *)0x41cc == 0) {
        FUN_1000_074c();
      }
      else {
        *(undefined2 *)0x5488 = 0;
        *(undefined2 *)0x9600 = 0;
        *(undefined2 *)0x933c = 0;
      }
    }
    for (; local_4 < *(uint *)0x160c; local_4 = local_4 + 1) {
      if (*(int *)0x9602 == 3) {
        FUN_1000_074c();
      }
      if (*(int *)0x41cc != 0) {
        uVar2 = *(uint *)0x9620;
        iVar6 = *(int *)0x9622;
        puVar1 = (uint *)0x9620;
        uVar9 = *puVar1;
        *puVar1 = *puVar1 + 1;
        *(int *)0x9622 = *(int *)0x9622 + (uint)(0xfffe < uVar9);
        if (((iVar6 != 0) || (0x8f < uVar2)) && ((*(int *)0x457c == 0 && (*(int *)0x4578 == 0)))) {
          *(undefined2 *)0x457c = 2;
          *(undefined2 *)0x4578 = 1;
          FUN_1000_03c2(0);
        }
      }
      local_16 = FUN_1000_04c0(*(undefined2 *)0x9628,*(undefined2 *)0x962a,*(undefined2 *)0xaf2c);
      bVar10 = local_16 != 0;
      if (bVar3) {
        if (0x2800 < *(uint *)0xaf3c) {
          if (*(int *)0xaf3c == *(int *)((local_16 >> 8) * 2 + 0xde)) {
            local_16 = local_16 >> 4;
          }
          else {
            local_16 = 0;
          }
        }
        FUN_1000_1a9c(local_16);
        bVar11 = (local_16 & 0xf) == 8;
        bVar12 = (local_16 & 0xf) == 2;
      }
      else {
        bVar12 = false;
      }
      lVar14 = FUN_1000_5d42();
      uVar9 = (uint)((ulong)(lVar14 + -0x8000) >> 0x10);
      if (((uVar9 <= *(uint *)0x962a) &&
          ((uVar9 < *(uint *)0x962a || ((uint)(lVar14 + -0x8000) <= *(uint *)0x9628)))) &&
         ((iVar6 = FUN_1000_0533(*(undefined2 *)0x9628,*(undefined2 *)0x962a,*(undefined2 *)0xaf2c,
                                 *(undefined2 *)0xaf3c), iVar6 != 0 && (*(int *)0x457c == 0)))) {
        uVar7 = FUN_1000_0e58();
        return uVar7;
      }
      if (*(int *)0xaf3c != local_1e) {
        if ((*(int *)0x54a2 == 0) || (1 < local_1a)) {
          if (*(int *)0x9342 < 1) {
            uVar9 = -*(int *)0x9342;
          }
          else {
            uVar9 = *(uint *)0x9342;
          }
          if (((uint)(((long)*(int *)0x456e * 0x104 & 0xffffU) / 8) <= uVar9) &&
             (*(int *)0x4578 == 0)) {
            if ((*(int *)0x457c == 0) &&
               ((*(int *)0x9342 < 0 && (iVar6 = FUN_1000_0476(), iVar6 == 0)))) {
              FUN_1000_03c2(1);
            }
            *(int *)0x9342 = (*(int *)0x9342 * -5) / 10;
            goto LAB_1000_249e;
          }
        }
        *(undefined2 *)0x9342 = 0;
      }
LAB_1000_249e:
      if (*(int *)0x457c == 0) {
        uVar13 = FUN_1000_5d0e(*(int *)0x933c,*(int *)0x933c >> 0xf,0x4b,0);
        puVar1 = (uint *)0x54b8;
        uVar9 = *puVar1;
        *puVar1 = *puVar1 + (uint)uVar13;
        *(int *)0x54ba =
             *(int *)0x54ba + (int)((ulong)uVar13 >> 0x10) + (uint)CARRY2(uVar9,(uint)uVar13);
        if ((*(int *)0x54ba < 1) && (*(int *)0x54ba < 0)) {
          *(undefined2 *)0x54b8 = 0;
          *(undefined2 *)0x54ba = 0;
        }
        else if ((-1 < *(int *)0x54ba) && ((0 < *(int *)0x54ba || (0x2aaa < *(uint *)0x54b8)))) {
          *(undefined2 *)0x54b8 = 0x2aaa;
          *(undefined2 *)0x54ba = 0;
        }
        if ((!bVar11) &&
           (((!bVar4 && (bVar10)) ||
            ((*(int *)0x4576 == 0 &&
             ((0 < *(int *)0x9342 && ((uint)(*(int *)0xaf3c - local_c) < 0xf00)))))))) {
          *(int *)0x4576 = *(int *)0x9600 * 0x1d;
        }
        if ((((!bVar4) && (bVar10)) && (*(int *)0x5488 != 0)) && (*(uint *)0x456e < 0x14)) {
          *(undefined2 *)0x9342 = 0x480;
          *(undefined2 *)0x54a0 = *(undefined2 *)0x54a0;
          bVar4 = true;
          local_c = *(int *)0xaf3c;
        }
      }
      if (((*(int *)0x457e != 0) && (bVar4)) && ((!bVar5 && (0x36ff < *(uint *)0xaf3c)))) {
        FUN_1000_1d4d();
        bVar5 = true;
      }
      if (*(int *)0x4578 == 0) {
        if (*(uint *)0xaf3c < 0x2800) {
          if (-0x6a < *(int *)0x9342) {
            *(undefined2 *)0x9342 = 0xff96;
          }
        }
        else {
          *(int *)0x9342 = *(int *)0x9342 + *(int *)0x54b6;
        }
      }
      else {
        if (*(int *)0x9342 < 0) {
          *(undefined2 *)0x9342 = 0;
        }
        if (*(int *)0x9342 < 0x47) {
          *(int *)0x9342 = *(int *)0x9342 + 0x27;
        }
        else {
          *(undefined2 *)0x9342 = 0x47;
        }
      }
      local_22 = *(uint *)0x54b8 + *(uint *)0x9628;
      local_20 = *(int *)0x54ba + *(int *)0x962a + (uint)CARRY2(*(uint *)0x54b8,*(uint *)0x9628);
      iVar6 = *(int *)0x54a2;
      if (bVar12 == false) {
        uVar9 = 0x618;
      }
      else {
        uVar9 = 0;
      }
      uVar13 = FUN_1000_5d0e(uVar9 + *(uint *)0x54b8,
                             *(int *)0x54ba + (uint)CARRY2(uVar9,*(uint *)0x54b8),*(int *)0x4576,
                             *(int *)0x4576 >> 0xf);
      iVar8 = FUN_1000_5e1c(uVar13,0x200,0);
      local_1c = iVar8 + *(int *)0xaf2c + iVar6;
      local_1e = *(int *)0x9342 + *(int *)0xaf3c;
      if (((*(uint *)0xaf2c < 0x2f80) && (0xd080 < local_1c)) ||
         ((local_1c < 0x2f80 && (0xd080 < *(uint *)0xaf2c)))) {
        local_1c = *(uint *)0xaf2c;
      }
      FUN_1000_17be(local_22,local_20,local_1c,local_1e);
      if ((((*(uint *)0x9628 != local_22) || (*(int *)0x962a != local_20)) &&
          (*(uint *)0xaf2c == local_1c)) &&
         (iVar6 = FUN_1000_1685(local_22,local_20,*(undefined2 *)0xaf2c,*(undefined2 *)0xaf3c),
         iVar6 != 0)) {
        iVar6 = FUN_1000_1685(local_22,local_20,*(int *)0xaf2c + -0x3a0,*(undefined2 *)0xaf3c);
        if (iVar6 == 0) {
          *(int *)0xaf2c = *(int *)0xaf2c + -0x3a0;
          local_22 = *(uint *)0x9628;
          local_20 = *(int *)0x962a;
          FUN_1000_03c2(2);
        }
        else {
          iVar6 = FUN_1000_1685(local_22,local_20,*(int *)0xaf2c + 0x3a0,*(undefined2 *)0xaf3c);
          if (iVar6 == 0) {
            *(int *)0xaf2c = *(int *)0xaf2c + 0x3a0;
            local_22 = *(uint *)0x9628;
            local_20 = *(int *)0x962a;
            FUN_1000_03c2(2);
          }
        }
      }
      if ((*(uint *)0x9628 != local_22) || (*(int *)0x962a != local_20)) {
        if (((*(int *)0x54ba < 0) || ((*(int *)0x54ba < 1 && (*(uint *)0x54b8 < 0xe38)))) ||
           (*(int *)0x4578 != 0)) {
          uVar9 = (local_20 - *(int *)0x54ba) - (uint)(local_22 < *(uint *)0x54b8);
          if ((uVar9 <= *(uint *)0x962a) &&
             ((uVar9 < *(uint *)0x962a || (local_22 - *(uint *)0x54b8 < *(uint *)0x9628)))) {
            FUN_1000_03c2(2);
          }
        }
        else {
          *(undefined2 *)0x4578 = 1;
          FUN_1000_03c2(0);
          if (*(int *)0x457c == 0) {
            *(undefined2 *)0x457c = 1;
          }
        }
        *(undefined2 *)0x54b8 = 0;
        *(undefined2 *)0x54ba = 0;
      }
      if (*(uint *)0xaf2c != local_1c) {
        *(undefined2 *)0x4576 = 0;
        if (((0 < *(int *)0x54a2) && (*(uint *)0xaf2c < local_1c)) ||
           ((*(int *)0x54a2 < 0 && (local_1c < *(uint *)0xaf2c)))) {
          *(undefined2 *)0x54a2 = 0;
        }
        puVar1 = (uint *)0x54b8;
        uVar9 = *puVar1;
        *puVar1 = *puVar1 - 0x97;
        *(int *)0x54ba = *(int *)0x54ba - (uint)(uVar9 < 0x97);
        if ((*(int *)0x54ba < 1) && (*(int *)0x54ba < 0)) {
          *(undefined2 *)0x54b8 = 0;
          *(undefined2 *)0x54ba = 0;
        }
        else if ((-1 < *(int *)0x54ba) && ((0 < *(int *)0x54ba || (0x2aaa < *(uint *)0x54b8)))) {
          *(undefined2 *)0x54b8 = 0x2aaa;
          *(undefined2 *)0x54ba = 0;
        }
      }
      bVar3 = false;
      if ((*(int *)0xaf3c != local_1e) && (*(int *)0x9342 < 0)) {
        *(undefined2 *)0x4568 = 0;
        bVar5 = false;
        bVar4 = false;
        bVar3 = true;
        uVar2 = *(uint *)0xaf3e;
        iVar6 = *(int *)0xaf40;
        puVar1 = (uint *)0x54b8;
        uVar9 = *puVar1;
        *puVar1 = *puVar1 - uVar2;
        *(int *)0x54ba = (*(int *)0x54ba - iVar6) - (uint)(uVar9 < uVar2);
        if ((*(int *)0x54ba < 1) && (*(int *)0x54ba < 0)) {
          *(undefined2 *)0x54b8 = 0;
          *(undefined2 *)0x54ba = 0;
        }
        else if ((-1 < *(int *)0x54ba) && ((0 < *(int *)0x54ba || (0x2aaa < *(uint *)0x54b8)))) {
          *(undefined2 *)0x54b8 = 0x2aaa;
          *(undefined2 *)0x54ba = 0;
        }
        *(undefined2 *)0xaf3e = 0;
        *(undefined2 *)0xaf40 = 0;
        local_24 = 0;
        for (local_18 = 1; local_18 < 0xf; local_18 = local_18 + 1) {
          iVar6 = FUN_1000_1685(*(undefined2 *)0x9628,*(undefined2 *)0x962a,
                                local_18 * 0x80 + *(int *)0xaf2c,*(int *)0xaf3c + -1);
          if (iVar6 == 0) {
            local_24 = 1;
            local_1a = local_18;
            break;
          }
        }
        for (local_18 = 1; local_18 < 0xf; local_18 = local_18 + 1) {
          iVar6 = FUN_1000_1685(*(undefined2 *)0x9628,*(undefined2 *)0x962a,
                                *(int *)0xaf2c + local_18 * -0x80,*(int *)0xaf3c + -1);
          if (iVar6 == 0) {
            local_24 = local_24 + -1;
            local_1a = local_18;
            break;
          }
        }
        if (local_24 == 0) {
          *(undefined2 *)0x54a2 = 0;
        }
        else {
          *(int *)0x54a2 = *(int *)0x54a2 + local_24 * 0x11;
        }
      }
      if (0x7fff < *(uint *)0xaf3c) {
        *(undefined2 *)0xaf3c = 0;
      }
      if (*(int *)0x457c == 0) {
        *(int *)0xb14c = *(int *)0xb14c - (int)(30000 / ((long)*(int *)0x4574 * 0x24 & 0xffffU));
        if (30000 < *(uint *)0xb14c) {
          *(undefined2 *)0xb14c = 0;
        }
        uVar13 = FUN_1000_5d0e((int)(30000 / (ulong)*(uint *)0x54ae),0,*(undefined2 *)0x54b8,
                               *(undefined2 *)0x54ba);
        iVar6 = FUN_1000_5e1c(uVar13,0,1);
        *(int *)0x54a0 = *(int *)0x54a0 - iVar6;
        if (30000 < *(uint *)0x54a0) {
          *(undefined2 *)0x54a0 = 0;
        }
      }
      if (*(int *)0x457c == 0) {
        if (*(uint *)0xaf3c < 0x2800) {
          *(undefined2 *)0x457c = 3;
        }
        if (*(int *)0x54a0 == 0) {
          *(undefined2 *)0x457c = 4;
        }
        if (*(int *)0xb14c == 0) {
          *(undefined2 *)0x457c = 5;
        }
      }
      else {
        *(int *)0x4566 = *(int *)0x4566 + 1;
      }
      if (*(int *)0x4578 != 0) {
        *(int *)0x4578 = *(int *)0x4578 + 1;
      }
    }
  } while( true );
}


// ---- FUN_1000_2af3 @ 1000:2af3 ----

undefined4 __cdecl16near FUN_1000_2af3(undefined2 param_1,undefined2 param_2)

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


// ---- FUN_1000_2b21 @ 1000:2b21 ----

int __cdecl16near FUN_1000_2b21(int param_1)

{
  int iVar1;
  int iVar2;
  int unaff_DS;
  
  *(int *)0xaf3a = unaff_DS + 0x31c;
  FUN_1000_3b81();
  *(undefined2 *)0xaf2e = 0;
  *(undefined2 *)0x456a = 0;
  *(undefined2 *)0x9618 = 0;
  *(undefined2 *)0x457a = 0;
  *(undefined2 *)0x41ca = 0;
  *(undefined2 *)0xaf30 = 0xffff;
  *(undefined2 *)0x9340 = 0;
  if (*(int *)0x36 == 0) {
    FUN_1000_2af3(0xa000,*(undefined2 *)0x517e);
    FUN_1000_2af3(0xa200,*(undefined2 *)0x517e);
  }
  else {
    FUN_1000_6015(0xac80,0xa000,0xac80,*(undefined2 *)0x517e,0x4d80);
  }
  FUN_1000_1067(0x60,0x9c,(*(int *)0x456e + -3) * 100,4);
  if (*(int *)0x36 == 0) {
    iVar1 = (uint)(*(int *)0x9340 == 0) * 0x200 + -0x6000;
  }
  else {
    iVar1 = *(int *)0x5486;
  }
  iVar1 = FUN_1000_0afa(0,0x2800,1,0,iVar1);
  iVar2 = FUN_1000_0b34(0x8000);
  FUN_1000_2d03(0x100,0x18,0x50,*(int *)0xaf44 + ((iVar2 * 3 + iVar1) * 3 + 0xe) * 0x2d0,
                *(undefined2 *)0xaf46);
  FUN_1000_4b72(0x41d0,1,0x24);
  iVar1 = FUN_1000_1f2c();
  if (*(int *)0x9340 != 0) {
    *(undefined2 *)0x9340 = 0;
    FUN_1000_0e23();
  }
  if (iVar1 == 0) {
    FUN_1000_3c7e();
    if (param_1 == 0) {
      FUN_1000_450a(0x68,0x50,0xd4e,99);
    }
    else {
      FUN_1000_450a(0x84,0x50,0xd46,99);
    }
    FUN_1000_443d(0x1b);
  }
  FUN_1000_4b72(0x41d0,0,0x24);
  FUN_1000_3be7();
  return iVar1;
}


// ---- FUN_1000_2cb2 @ 1000:2cb2 ----

undefined2 __cdecl16near FUN_1000_2cb2(void)

{
  undefined2 uVar1;
  undefined2 unaff_DS;
  
  uVar1 = FUN_1000_3a7a();
  *(undefined2 *)0xe44 = 0x348b;
  *(undefined2 *)0xe46 = 0x3137;
  *(undefined2 *)0xe48 = 0x3174;
  *(undefined2 *)0xe4a = 0x323f;
  if (*(int *)0x36 != 1) {
    *(undefined2 *)0xe44 = 0x3462;
    *(undefined2 *)0xe46 = 0x3083;
    *(undefined2 *)0xe48 = 0x30d9;
    *(undefined2 *)0xe4a = 0x31bf;
    FUN_1000_3a23();
    out(0x3ce,5);
    out(0x3ce,0xf01);
    uVar1 = 3;
    out(0x3ce,3);
  }
  return uVar1;
}


// ---- FUN_1000_2d03 @ 1000:2d03 ----

void __cdecl16near
FUN_1000_2d03(undefined2 param_1,undefined2 param_2,undefined2 param_3,undefined2 param_4,
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
  *(undefined2 *)0xe34 = param_1;
  *(undefined2 *)0xe36 = param_2;
  *(undefined2 *)0xe38 = param_3;
  *(undefined2 *)0xe3a = param_4;
  *(undefined2 *)0xe3c = param_5;
  *(undefined2 *)0xe3e = param_6;
  *(undefined2 *)0xe40 = param_7;
  *(undefined2 *)0xe42 = param_8;
  (*(code *)*(undefined2 *)0xe44)();
  iVar4 = (*(uint *)0xe36 >> 3) * 0xe + 0x169a;
  *(undefined2 *)0xe56 = 0;
  *(undefined2 *)0xe50 = 0xb;
  do {
    while( true ) {
      *(undefined2 *)0xe54 = 0;
      *(undefined2 *)0xe4c = *(undefined2 *)0xe46;
      do {
        *(undefined2 *)0xe52 = 4;
        do {
          (*(code *)*(undefined2 *)((*(byte *)(iVar4 + 1) & 0xf) * 2 + 0xb7f))(puVar8);
          iVar5 = iVar4 + 2;
          if (*(int *)0xe54 != 0) {
            iVar5 = iVar4 + -2;
          }
          piVar1 = (int *)0xe52;
          *piVar1 = *piVar1 + -1;
          iVar4 = iVar5;
        } while (*piVar1 != 0);
        iVar4 = iVar5 + 4;
        *(undefined2 *)0xe4c = *(undefined2 *)0xe48;
        *(int *)0xe54 = *(int *)0xe54 + 1;
      } while (*(uint *)0xe54 < 2);
      if ((*(int *)0xe50 != 4) || (*(int *)0xe56 = *(int *)0xe56 + 1, 1 < *(uint *)0xe56)) break;
      iVar4 = iVar5 + -4;
      puVar8 = (undefined1 *)0x2e0e;
      (*(code *)*(undefined2 *)0xe4a)();
    }
    iVar4 = iVar5 + -0x12;
    piVar1 = (int *)0xe50;
    *piVar1 = *piVar1 + -1;
  } while (*piVar1 != 0);
  FUN_1000_3492();
  *(undefined2 *)0xe76 = *(undefined2 *)0xe36;
  *(undefined2 *)0xe7a = *(undefined2 *)0xe78;
  *(undefined2 *)0xe7e = *(undefined2 *)0xe7c;
  puVar6 = (undefined2 *)0xe92;
  puVar7 = (undefined2 *)0x124f;
  for (iVar4 = 0x1de; iVar4 != 0; iVar4 = iVar4 + -1) {
    puVar3 = puVar7;
    puVar7 = puVar7 + 1;
    puVar2 = puVar6;
    puVar6 = puVar6 + 1;
    *puVar3 = *puVar2;
  }
  return;
}


// ---- FUN_1000_3492 @ 1000:3492 ----

void __cdecl16near FUN_1000_3492(void)

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
  
  if (*(int *)0x36 == 0) {
    return;
  }
  *(undefined2 *)0xe72 = *(undefined2 *)0x517e;
  *(undefined2 *)0xe74 = *(undefined2 *)0xe42;
  *(undefined2 *)0xe4e = 0x3633;
  if (in_AX != 0) {
    *(undefined2 *)0xe72 = *(undefined2 *)0xe42;
    *(undefined2 *)0xe74 = 0xa000;
    *(undefined2 *)0xe4e = 0x36d7;
  }
  if (*(int *)0xe3e == 0) {
    if (*(int *)0xe36 == *(int *)0xe76) goto LAB_1000_360b;
    if ((uint)(*(int *)0xe36 - *(int *)0xe76) < 8) {
      *(undefined2 *)0xe70 = 0;
      if (*(uint *)0xe36 >> 3 == *(uint *)0xe76 >> 3) {
        *(int *)0xe70 = *(int *)0xe70 + 0x30;
      }
      *(undefined2 *)0xe6e = *(undefined2 *)((*(uint *)0xe76 & 7) * 2 + 0xe82);
      *(undefined2 *)0xe6c = *(undefined2 *)((*(uint *)0xe36 & 7) * 2 + 0xe82);
      *(int *)0xe58 = (*(uint *)0xe36 >> 3) * 0xe + 0x169a;
      *(undefined2 *)0xe50 = 0xb;
      do {
        *(undefined2 *)0xe52 = 1;
        do {
          *(undefined2 *)0xe54 = 0;
          do {
            iVar6 = -*(int *)0xe52 + 4;
            if (*(int *)0xe54 == 1) {
              iVar6 = -(-*(int *)0xe52 + -2);
            }
            pbVar7 = (byte *)(*(int *)0xe58 + iVar6 * 2);
            *(uint *)0xe62 = *pbVar7 & 0xf;
            *(uint *)0xe68 = (uint)(*pbVar7 >> 4);
            *(uint *)0xe5a = (uint)*(byte *)((pbVar7[1] & 7) + 0xb77);
            *(uint *)0xe64 = pbVar7[-0xe] & 0xf;
            *(uint *)0xe6a = (uint)(pbVar7[-0xe] >> 4);
            *(uint *)0xe5c = (uint)*(byte *)((pbVar7[-0xd] & 7) + 0xb77);
            iVar6 = *(int *)0xe54 * -4;
            *(uint *)0xe66 = pbVar7[iVar6 + 2] & 0xf;
            *(uint *)0xe5e = (uint)*(byte *)((pbVar7[iVar6 + 3] & 7) + 0xb77);
            *(uint *)0xe60 = (uint)*(byte *)((pbVar7[iVar6 + -0xb] & 7) + 0xb77);
            (*(code *)*(undefined2 *)0xe4e)();
            puVar1 = (uint *)0xe54;
            *puVar1 = *puVar1 ^ 1;
          } while (*puVar1 != 0);
          *(int *)0xe52 = *(int *)0xe52 + 1;
        } while (*(uint *)0xe52 < 5);
        *(int *)0xe58 = *(int *)0xe58 + -0xe;
        *(int *)0xe50 = *(int *)0xe50 + -1;
      } while (*(int *)0xe50 != 1);
      goto LAB_1000_360b;
    }
  }
  puVar8 = (undefined2 *)0x2800;
  iVar6 = 0x4240;
  if (*(int *)0xe3e != 0) {
    puVar8 = (undefined2 *)0x0;
    iVar6 = 0x5640;
  }
  uVar4 = *(undefined2 *)0xe72;
  uVar5 = *(undefined2 *)0xe74;
  puVar9 = puVar8;
  for (; iVar6 != 0; iVar6 = iVar6 + -1) {
    puVar3 = puVar9;
    puVar9 = puVar9 + 1;
    puVar2 = puVar8;
    puVar8 = puVar8 + 1;
    *puVar3 = *puVar2;
  }
LAB_1000_360b:
  FUN_1000_39b8();
  return;
}


// ---- FUN_1000_39b8 @ 1000:39b8 ----

void __cdecl16near FUN_1000_39b8(void)

{
  undefined2 unaff_SS;
  
  FUN_1000_3a06();
  FUN_1000_3a06();
  if (*(int *)0xe74 == -0x6000) {
    FUN_1000_3a06();
    FUN_1000_3a06();
  }
  return;
}


// ---- FUN_1000_3a06 @ 1000:3a06 ----

void __cdecl16near FUN_1000_3a06(void)

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


// ---- FUN_1000_3a23 @ 1000:3a23 ----

void __cdecl16near FUN_1000_3a23(void)

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
    uVar2 = *(undefined2 *)(iVar9 + 0xe82);
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


// ---- FUN_1000_3a7a @ 1000:3a7a ----

void __cdecl16near FUN_1000_3a7a(void)

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
    uVar4 = *(undefined2 *)(iVar7 + 0xe82);
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


// ---- FUN_1000_3ab0 @ 1000:3ab0 ----

uint __cdecl16near FUN_1000_3ab0(void)

{
  uint uVar1;
  
  uVar1 = uRam00000020;
  DAT_1000_3b4b = uRam00000020;
  DAT_1000_3b4d = uRam00000022;
  uRam00000020 = 0x3afb;
  uRam00000022 = 0x1000;
  uRam00000090 = 0x3af8;
  uRam00000092 = 0x1000;
  out(0x43,0x36);
  out(0x40,0xe4);
  out(0x40,0x19);
  out(0x43,0xb6);
  out(0x42,2);
  out(0x42,0);
  return uVar1 & 0xff00;
}


// ---- FUN_1000_3b4f @ 1000:3b4f ----

uint __cdecl16near FUN_1000_3b4f(void)

{
  undefined1 uVar1;
  uint uVar2;
  
  uRam00000020 = DAT_1000_3b4b;
  uRam00000022 = DAT_1000_3b4d;
  out(0x43,0x36);
  out(0x40,0);
  out(0x40,0);
  out(0x43,0xb6);
  out(0x42,0);
  out(0x42,0);
  uVar1 = in(0x61);
  uVar2 = CONCAT11((char)((uint)DAT_1000_3b4b >> 8),uVar1) & 0xfffc;
  out(0x61,(char)uVar2);
  return uVar2;
}


// ---- FUN_1000_3b81 @ 1000:3b81 ----

void __cdecl16near FUN_1000_3b81(void)

{
  byte *pbVar1;
  int iVar2;
  undefined2 unaff_DS;
  
  iVar2 = -1;
  do {
    pbVar1 = (byte *)(iVar2 + 0xba3);
    *pbVar1 = *pbVar1 & 0x7f;
    iVar2 = iVar2 + 1;
  } while (*pbVar1 != 0);
  DAT_1000_3be3 = uRam00000024;
  DAT_1000_3be5 = uRam00000026;
  uRam00000024 = 0x3bb0;
  uRam00000026 = 0x1000;
  return;
}


// ---- FUN_1000_3be7 @ 1000:3be7 ----

void __cdecl16near FUN_1000_3be7(void)

{
  uRam00000024 = DAT_1000_3be3;
  uRam00000026 = DAT_1000_3be5;
  return;
}


// ---- FUN_1000_3c36 @ 1000:3c36 ----

void __cdecl16near FUN_1000_3c36(int param_1,int param_2,int param_3,undefined1 param_4)

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
  
  pbVar7 = (byte *)(param_3 * 8 + *(int *)0x3190);
  uVar2 = *(undefined2 *)0x3192;
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


// ---- FUN_1000_3c7e @ 1000:3c7e ----

void __cdecl16near FUN_1000_3c7e(void)

{
  undefined2 unaff_DS;
  
  if (*(char *)0x36 == '\0') {
    out(0x3ce,0x205);
    out(0x3ce,0xf01);
    out(0x3ce,3);
  }
  return;
}


// ---- FUN_1000_3c95 @ 1000:3c95 ----

void __cdecl16near
FUN_1000_3c95(undefined2 param_1,uint param_2,int param_3,int param_4,undefined2 param_5)

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
                    /* WARNING: Read-only address (ram,0x00013cd9) is written */
  uRam00013cd9 = param_5;
  iRam00013ce4 = param_4 + -1;
                    /* WARNING: Read-only address (ram,0x00013ce4) is written */
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


// ---- FUN_1000_3cfc @ 1000:3cfc ----

void __cdecl16near FUN_1000_3cfc(byte *param_1,undefined2 param_2)

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
  
  uVar2 = *(undefined2 *)0x962c;
  pbVar10 = (byte *)((uint)param_1 >> 3);
                    /* WARNING: Read-only address (ram,0x00013d57) is written */
  uRam00013d57 = param_2;
  iRam00013d6f = *(int *)0x961e + -1;
                    /* WARNING: Read-only address (ram,0x00013d6f) is written */
  uRam00013d62 = *(undefined1 *)0xaf4a;
                    /* WARNING: Read-only address (ram,0x00013d62) is written */
  uRam00013d5e = *(undefined1 *)0x9624;
                    /* WARNING: Read-only address (ram,0x00013d5e) is written */
  uVar3 = CONCAT11(0x80 >> ((byte)param_1 & 7),8);
  iVar6 = *(int *)0x961e;
  pbVar8 = (byte *)0x0;
  uVar12 = *(undefined2 *)0x4522;
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
          uVar12 = *(undefined2 *)0x4522;
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


// ---- FUN_1000_3d82 @ 1000:3d82 ----

void __cdecl16near FUN_1000_3d82(undefined2 param_1,int param_2,uint param_3,uint param_4)

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
      uVar3 = *(uint *)((*puVar2 & 0xff) * 2 + -0x50b4);
      uVar1 = *(undefined2 *)((*puVar2 >> 8) * 2 + -0x50b4);
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
      uVar5 = *(uint *)((uint)(byte)*puVar2 * 2 + -0x50b4);
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


// ---- FUN_1000_3df3 @ 1000:3df3 ----

void __cdecl16near FUN_1000_3df3(uint param_1,byte param_2,int param_3)

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


// ---- FUN_1000_3e30 @ 1000:3e30 ----

undefined4 __cdecl16near FUN_1000_3e30(uint param_1,byte param_2)

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


// ---- FUN_1000_3e6e @ 1000:3e6e ----

void __cdecl16near FUN_1000_3e6e(uint param_1,uint param_2,int param_3,int param_4)

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
  uVar3 = *(undefined4 *)0x3190;
  pbVar5 = (byte *)((int)uVar3 + param_3 * 8);
  pbVar6 = (byte *)((param_2 & 0xff) * 0x28 + (param_1 >> 3));
  cRam00013ebe = -(((byte)param_1 & 7) - 8);
                    /* WARNING: Read-only address (ram,0x00013ebe) is written */
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


// ---- FUN_1000_3ed8 @ 1000:3ed8 ----

undefined2 __cdecl16near FUN_1000_3ed8(undefined2 param_1,undefined2 param_2)

{
  undefined2 uVar1;
  undefined2 unaff_DS;
  
  uVar1 = FUN_1000_6202(param_1,param_2);
  *(undefined2 *)(*(int *)0x4572 * 2 + -0x6cbc) = uVar1;
  *(int *)0x4572 = *(int *)0x4572 + 1;
  return uVar1;
}


// ---- FUN_1000_3f04 @ 1000:3f04 ----

void __cdecl16near FUN_1000_3f04(void)

{
  undefined2 unaff_DS;
  
  *(undefined2 *)(*(int *)0x4572 * 2 + -0x6cbc) = 1;
  *(int *)0x4572 = *(int *)0x4572 + 1;
  return;
}


// ---- FUN_1000_3f1f @ 1000:3f1f ----

void __cdecl16near FUN_1000_3f1f(void)

{
  undefined2 unaff_DS;
  
  *(int *)0x4572 = *(int *)0x4572 + -1;
  while (*(int *)(*(int *)0x4572 * 2 + -0x6cbc) != 1) {
    FUN_1000_6061(*(undefined2 *)(*(int *)0x4572 * 2 + -0x6cbc));
    *(int *)0x4572 = *(int *)0x4572 + -1;
  }
  return;
}


// ---- FUN_1000_3f56 @ 1000:3f56 ----

void __cdecl16near FUN_1000_3f56(void)

{
  undefined2 unaff_DS;
  
  *(int *)0x4572 = *(int *)0x4572 + -1;
  FUN_1000_6061(*(undefined2 *)(*(int *)0x4572 * 2 + -0x6cbc));
  return;
}


// ---- FUN_1000_3f75 @ 1000:3f75 ----

undefined2 __cdecl16near FUN_1000_3f75(int param_1,int param_2)

{
  undefined2 uVar1;
  undefined2 unaff_DS;
  
  FUN_1000_64f0();
  FUN_1000_64f0();
  uVar1 = FUN_1000_640a();
  if (*(int *)0x41b6 == 0) {
    FUN_1000_650f(param_1 + param_2 * 3);
  }
  FUN_1000_650f(0xaf4c);
  return uVar1;
}


// ---- FUN_1000_3fc6 @ 1000:3fc6 ----

undefined2 __cdecl16near FUN_1000_3fc6(undefined2 *param_1,undefined2 param_2)

{
  undefined2 uVar1;
  undefined2 unaff_DS;
  
  FUN_1000_64f0();
  FUN_1000_64f0();
  param_1[1] = param_2;
  uVar1 = FUN_1000_640a();
  param_1[2] = uVar1;
  uVar1 = FUN_1000_3ed8(param_1[2] * 3,0);
  *param_1 = uVar1;
  if (*(int *)0x41b6 == 0) {
    FUN_1000_650f(0,uVar1,param_1[2] * 3);
    FUN_1000_650f(0xaf4c);
  }
  return param_1[2];
}


// ---- FUN_1000_4036 @ 1000:4036 ----

void __cdecl16near FUN_1000_4036(char *param_1,int param_2,int param_3,char param_4)

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


// ---- FUN_1000_4068 @ 1000:4068 ----

void __cdecl16near FUN_1000_4068(undefined2 *param_1,undefined2 param_2)

{
  int iVar1;
  undefined2 uVar2;
  undefined2 unaff_DS;
  
  FUN_1000_64f0();
  FUN_1000_650f(param_1);
  iVar1 = param_1[2] * param_1[3];
  uVar2 = FUN_1000_3ed8(iVar1,0);
  *param_1 = uVar2;
  FUN_1000_0069();
  FUN_1000_6660(0,uVar2,iVar1);
  if (*(int *)0x36 == 0) {
    FUN_1000_3d82(*param_1,param_1[2],param_1[3],param_1[1] & 1 ^ (uint)param_1[1] / 0x140 & 1);
  }
  else {
    FUN_1000_4036(0,uVar2,iVar1,0,param_2);
  }
  return;
}


// ---- FUN_1000_40ff @ 1000:40ff ----

void __cdecl16near FUN_1000_40ff(undefined2 param_1)

{
  undefined2 uVar1;
  
  uVar1 = FUN_1000_5c38(param_1,0,0x1000,0);
  FUN_1000_639a(uVar1);
  return;
}


// ---- FUN_1000_4120 @ 1000:4120 ----

void __cdecl16near FUN_1000_4120(void)

{
  undefined2 unaff_DS;
  
  FUN_1000_5c1a(*(undefined2 *)0x41b8);
  FUN_1000_0069();
  return;
}


// ---- FUN_1000_4137 @ 1000:4137 ----

void __cdecl16near FUN_1000_4137(void)

{
  int iVar1;
  undefined2 unaff_DS;
  
  while (iVar1 = FUN_1000_5f8e(), iVar1 != 0) {
    FUN_1000_5fad();
    if (*(int *)0xaf42 != 0) {
      *(undefined2 *)0x54ac = 1;
    }
  }
  return;
}


// ---- FUN_1000_4162 @ 1000:4162 ----

void __cdecl16near
FUN_1000_4162(undefined2 param_1,undefined2 param_2,undefined1 param_3,undefined1 param_4)

{
  undefined2 unaff_DS;
  
  *(undefined2 *)0x4520 = param_1;
  *(undefined2 *)0x962c = param_2;
  *(undefined1 *)0xaf4a = param_3;
  *(undefined1 *)0x9624 = param_4;
  return;
}


// ---- FUN_1000_4184 @ 1000:4184 ----

void __cdecl16near FUN_1000_4184(byte *param_1,byte *param_2,int param_3,int param_4)

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
  
  uRam000141cd = *(undefined1 *)0x9624;
                    /* WARNING: Read-only address (ram,0x000141cd) is written */
  bVar3 = *(byte *)0xaf4a;
  uVar4 = *(undefined2 *)0x4520;
  uVar5 = *(undefined2 *)0x4522;
  uVar6 = *(undefined2 *)0x962c;
  pbVar9 = param_1;
  for (iVar8 = param_3; iVar8 != 0; iVar8 = iVar8 + -1) {
    pbVar2 = pbVar9;
    pbVar9 = pbVar9 + 1;
    pbVar1 = param_1;
    param_1 = param_1 + 1;
    *pbVar2 = *pbVar1;
  }
  iVar8 = (*(int *)0x961e - param_3) - param_4;
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


// ---- FUN_1000_41e5 @ 1000:41e5 ----

void __cdecl16near FUN_1000_41e5(undefined2 *param_1)

{
  uint uVar1;
  undefined2 unaff_DS;
  int local_8;
  int local_6;
  
  *(undefined2 *)0x4522 = *param_1;
  *(undefined2 *)0x961e = param_1[3];
  if (((*(uint *)0x962c & 0xa000) == 0xa000) && (*(int *)0x36 == 0)) {
    FUN_1000_3cfc(param_1[1],param_1[2]);
  }
  else {
    local_8 = param_1[1];
    local_6 = 0;
    for (uVar1 = 0; uVar1 < (uint)param_1[2]; uVar1 = uVar1 + 1) {
      FUN_1000_4184(local_8,local_6,0,0);
      local_8 = local_8 + 0x140;
      local_6 = local_6 + param_1[3];
    }
  }
  return;
}


// ---- FUN_1000_4260 @ 1000:4260 ----

void __cdecl16near FUN_1000_4260(undefined2 *param_1)

{
  undefined2 unaff_DS;
  
  if (*(int *)0x36 != 0) {
    FUN_1000_6233(param_1[1],param_1[2],0,*param_1);
  }
  return;
}


// ---- FUN_1000_4293 @ 1000:4293 ----

void __cdecl16near FUN_1000_4293(undefined2 *param_1)

{
  undefined2 uVar1;
  uint uVar2;
  undefined2 unaff_DS;
  int local_c;
  int local_8;
  
  if (*(int *)0x36 == 0) {
    FUN_1000_3c95(*param_1,param_1[1],0,param_1[3],param_1[2]);
  }
  else {
    local_c = param_1[1];
    uVar1 = *param_1;
    local_8 = 0;
    for (uVar2 = 0; uVar2 < (uint)param_1[2]; uVar2 = uVar2 + 1) {
      FUN_1000_6015(local_c,0xa000,local_8,uVar1,param_1[3]);
      local_c = local_c + 0x140;
      local_8 = local_8 + param_1[3];
    }
  }
  return;
}


// ---- FUN_1000_4315 @ 1000:4315 ----

void __cdecl16near FUN_1000_4315(uint *param_1,uint *param_2,uint param_3)

{
  undefined2 unaff_DS;
  char *local_10;
  byte *local_e;
  byte *local_a;
  int local_6;
  uint local_4;
  
  if (*(int *)0x36 != 0) {
    *(undefined2 *)0x160c = 0;
    do {
      if (param_3 == 0) {
        local_6 = 100;
      }
      else {
        local_6 = (int)(((long)*(int *)0x160c * 100 & 0xffffU) / (ulong)param_3);
      }
      if ((100 < local_6) || (*(int *)0x54ac != 0)) {
        local_6 = 100;
      }
      local_10 = (char *)0x31b4;
      local_a = (byte *)((ulong)*param_1 << 0x10);
      local_e = (byte *)((ulong)*param_2 << 0x10);
      for (local_4 = 0; local_4 < param_1[2] * 3; local_4 = local_4 + 1) {
        *local_10 = *local_a + (char)((int)(((uint)*local_e - (uint)*local_a) * local_6) / 100);
        local_10 = local_10 + 1;
        local_a = (byte *)CONCAT22(local_a._2_2_,(byte *)local_a + 1);
        local_e = (byte *)CONCAT22(local_e._2_2_,(byte *)local_e + 1);
      }
      FUN_1000_6233(param_1[1],param_1[2],0x31b4);
      FUN_1000_4137();
    } while (local_6 != 100);
  }
  return;
}


// ---- FUN_1000_443d @ 1000:443d ----

void __cdecl16near FUN_1000_443d(uint param_1)

{
  undefined2 unaff_DS;
  
  *(undefined2 *)0x160c = 0;
  while ((*(uint *)0x160c < param_1 && (*(int *)0x54ac == 0))) {
    FUN_1000_4137();
  }
  return;
}


// ---- FUN_1000_4469 @ 1000:4469 ----

void __cdecl16near FUN_1000_4469(int param_1,int param_2)

{
  undefined2 unaff_DS;
  
  FUN_1000_6015(param_1 + *(int *)(param_2 + 2) * 3);
  return;
}


// ---- FUN_1000_44a2 @ 1000:44a2 ----

void __cdecl16near
FUN_1000_44a2(undefined2 param_1,undefined2 param_2,uint param_3,undefined2 param_4)

{
  undefined2 uVar1;
  undefined2 unaff_DS;
  
  uVar1 = *(undefined2 *)0x3196;
  *(undefined2 *)0x3190 = *(undefined2 *)0x3194;
  *(undefined2 *)0x3192 = uVar1;
  if ((param_3 & 0x80) != 0) {
    param_3 = param_3 & 0x7f;
    uVar1 = *(undefined2 *)0x319a;
    *(undefined2 *)0x3190 = *(undefined2 *)0x3198;
    *(undefined2 *)0x3192 = uVar1;
  }
  if (*(int *)0x36 == 0) {
    FUN_1000_3e6e(param_1,param_2,param_3,0xf);
  }
  else {
    FUN_1000_3c36(param_1,param_2,param_3,param_4);
  }
  return;
}


// ---- FUN_1000_450a @ 1000:450a ----

void __cdecl16near FUN_1000_450a(int param_1,undefined2 param_2,char *param_3,undefined2 param_4)

{
  undefined2 unaff_DS;
  
  while (*param_3 != '\0') {
    FUN_1000_44a2(param_1,param_2,*param_3,param_4);
    param_1 = param_1 + 8;
    param_3 = param_3 + 1;
  }
  return;
}


// ---- FUN_1000_4547 @ 1000:4547 ----

void __cdecl16near FUN_1000_4547(int param_1,int param_2,int param_3)

{
  undefined2 unaff_DS;
  
  *(int *)0xbc6 = param_2 * 0x140 + param_1;
  *(int *)0xbca = param_3 << 3;
  FUN_1000_3c7e();
  FUN_1000_41e5(0xbc4);
  return;
}


// ---- FUN_1000_4575 @ 1000:4575 ----

int __cdecl16near FUN_1000_4575(void)

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
  FUN_1000_3f04();
  FUN_1000_57a8(0);
  FUN_1000_40ff(0xd5e);
  FUN_1000_3fc6(local_62,0);
  FUN_1000_4068(local_14,0);
  FUN_1000_3fc6(local_68,0x32);
  FUN_1000_3fc6(local_6e,0x32);
  FUN_1000_4068(&local_24,0x32);
  for (local_4 = 0; (int)local_4 < 7; local_4 = local_4 + 1) {
    FUN_1000_3fc6(local_b0 + local_4 * 6,0xa0);
    FUN_1000_3fc6(local_da + local_4 * 6,0xa0);
    FUN_1000_4068(local_5c + local_4 * 8,0xa0);
  }
  FUN_1000_4120();
  FUN_1000_40ff(0xd68);
  FUN_1000_64f0();
  FUN_1000_64f0();
  uVar2 = FUN_1000_64f0();
  FUN_1000_3fc6(local_86,0);
  local_de = 0;
  for (local_4 = 0; local_4 < uVar2; local_4 = local_4 + 1) {
    uVar3 = FUN_1000_64f0();
    for (local_e0 = 0; local_e0 < uVar3; local_e0 = local_e0 + 1) {
      *(uint *)(local_de * 10 + 0x45c4) = local_4;
      FUN_1000_4068(local_de * 10 + 0x45c6,0);
      local_de = local_de + 1;
      if (local_de == 300) {
        *(undefined2 *)0x41b6 = 0x40;
        FUN_1000_0069();
      }
    }
  }
  FUN_1000_4120();
  uVar5 = *(undefined2 *)0x456c;
  uVar4 = FUN_1000_5c38(0xd72,0,uVar5,0x7d64);
  *(undefined2 *)0x41b8 = uVar4;
  FUN_1000_5f77(uVar4);
  FUN_1000_4120();
  *(undefined2 *)0x54ac = 0;
  *(undefined2 *)0xaf42 = 1;
  FUN_1000_3c7e();
  FUN_1000_5cc8(0x5182,0,0x300);
  FUN_1000_4b72(0x5182,0,0);
  FUN_1000_4469(0x5182,local_86);
  FUN_1000_4293(local_14);
  FUN_1000_4b72(0x5182,1,0x24);
  FUN_1000_443d(0x18);
  if (*(int *)0x54ac == 0) {
    FUN_1000_5b5a(0,uVar5,0x5a,0x7d64);
  }
  FUN_1000_443d(0x25);
  if (*(int *)0x54ac == 0) {
    *(undefined2 *)0x160c = 0;
    for (local_4 = 0; local_4 < local_de; local_4 = local_4 + 1) {
      if (*(int *)(local_4 * 10 + 0x45c4) != local_e4) {
        do {
        } while (*(uint *)0x160c < 2);
        *(undefined2 *)0x160c = 0;
        local_e4 = *(int *)(local_4 * 10 + 0x45c4);
      }
      FUN_1000_4293(local_4 * 10 + 0x45c6);
      FUN_1000_4137();
      if (*(int *)0x54ac != 0) {
        FUN_1000_4293(local_14);
        break;
      }
    }
  }
  *(undefined2 *)0x961e = 0x140;
  *(undefined2 *)0x4522 = local_24;
  FUN_1000_4162(local_14[0],0xa000,1,0);
  FUN_1000_443d(0x48);
  if (*(int *)0x36 == 0) {
    FUN_1000_41e5(&local_24);
  }
  else {
    FUN_1000_4260(local_68);
    *(undefined2 *)0x160c = 0;
    do {
      local_4 = 0x13f - (int)(((long)*(int *)0x160c * 0x13f & 0xffffU) / 0x12);
      if (((int)local_4 < 0) || (*(int *)0x54ac != 0)) {
        local_4 = 0;
      }
      local_a = local_22;
      local_c = 0;
      for (local_6 = 0; local_6 < local_20; local_6 = local_6 + 2) {
        FUN_1000_4184(local_a,local_c,local_4,0);
        FUN_1000_4184(local_a + 0x140,local_c + 0x140 + local_4,0,local_4);
        local_a = local_a + 0x280;
        local_c = local_c + local_1e * 2;
      }
    } while (local_4 != 0);
    FUN_1000_5ca4(local_74,local_68,6);
    uVar5 = FUN_1000_3ed8(local_64 * 3,0);
    local_74[0] = uVar5;
    FUN_1000_0069();
    FUN_1000_5c92(0,uVar5,0x3f,local_64 * 3);
    if (*(int *)0x54ac == 0) {
      FUN_1000_4315(local_68,local_74,5);
      FUN_1000_443d(9);
      FUN_1000_4315(local_74,local_6e,0x46);
    }
    else {
      FUN_1000_4315(local_68,local_6e,5);
    }
  }
  bVar1 = false;
  while (!bVar1) {
    local_4 = 2;
    while (((int)local_4 < 7 && (*(int *)0x54ac == 0))) {
      FUN_1000_4260(local_b0 + local_4 * 6);
      FUN_1000_4162(local_14[0],0xa000,1,0);
      FUN_1000_41e5(local_5c + local_4 * 8);
      FUN_1000_4315(local_b0 + local_4 * 6,local_da + local_4 * 6,0x32);
      FUN_1000_443d(0x32);
      if (*(int *)0x36 == 0) {
        FUN_1000_443d(100);
      }
      FUN_1000_4315(local_da + local_4 * 6,local_b0 + local_4 * 6,0x32);
      *(undefined1 *)0xaf4a = 0xff;
      FUN_1000_41e5(local_5c + local_4 * 8);
      local_4 = local_4 + 1;
    }
    bVar1 = true;
  }
  local_4 = *(int *)0x54ac;
  *(undefined2 *)0x54ac = 0;
  *(undefined2 *)0xaf42 = 0;
  if (local_4 == 0) {
    FUN_1000_4469(0x5182,local_62);
    FUN_1000_4469(0x5182,local_6e);
    FUN_1000_4b72(0x5182,0,0x24);
  }
  FUN_1000_3f1f();
  return local_4;
}


// ---- FUN_1000_4aaf @ 1000:4aaf ----

void __cdecl16near FUN_1000_4aaf(int param_1,undefined2 param_2)

{
  undefined2 unaff_DS;
  
  FUN_1000_4162(*(undefined2 *)0xaf32,0xa000,param_2,1);
  FUN_1000_41e5(param_1 * 8 + 0x44d0);
  return;
}


// ---- FUN_1000_4ae2 @ 1000:4ae2 ----

void __cdecl16near FUN_1000_4ae2(void)

{
  undefined2 uVar1;
  uint uVar2;
  undefined2 unaff_DS;
  
  for (uVar2 = 0; uVar2 < 5; uVar2 = uVar2 + 1) {
    uVar1 = 0xff;
    if ((uVar2 == *(uint *)0x4526) || (uVar2 == *(int *)0x4528 + 3U)) {
      uVar1 = 1;
    }
    FUN_1000_4aaf(uVar2 + 5,uVar1);
  }
  return;
}


// ---- FUN_1000_4b27 @ 1000:4b27 ----

void __cdecl16near FUN_1000_4b27(undefined2 *param_1,undefined2 param_2)

{
  undefined2 uVar1;
  undefined2 unaff_DS;
  
  uVar1 = FUN_1000_3ed8(0x300,0);
  *param_1 = uVar1;
  FUN_1000_0069();
  FUN_1000_6015(0,uVar1,param_2);
  param_1[1] = 0;
  param_1[2] = 0x100;
  return;
}


// ---- FUN_1000_4b72 @ 1000:4b72 ----

void __cdecl16near FUN_1000_4b72(undefined2 param_1,int param_2,undefined2 param_3)

{
  undefined2 uVar1;
  undefined2 unaff_DS;
  undefined1 local_e [6];
  undefined1 local_8 [6];
  
  FUN_1000_5cc8(0x31b4,0,0x300);
  if (*(int *)0x36 == 0) {
    FUN_1000_5fc8();
    if (param_2 == 0) {
      uVar1 = 0x31b4;
    }
    else {
      uVar1 = 0xbb0;
    }
    FUN_1000_60c1(uVar1);
    FUN_1000_5fc8();
  }
  else {
    FUN_1000_3f04();
    FUN_1000_4b27(local_8,param_1);
    FUN_1000_4b27(local_e,0x31b4);
    if (param_2 == 0) {
      FUN_1000_4315(local_8,local_e,param_3);
    }
    else {
      FUN_1000_4315(local_e,local_8,param_3);
    }
    FUN_1000_3f1f();
  }
  return;
}


// ---- FUN_1000_4c04 @ 1000:4c04 ----

void __cdecl16near FUN_1000_4c04(void)

{
  int iVar1;
  undefined2 unaff_DS;
  uint local_8;
  uint local_6;
  uint local_4;
  
  local_4 = 0;
  local_6 = 0;
  FUN_1000_3f04();
  FUN_1000_40ff(0xd7c);
  FUN_1000_3f75(0x5182,200);
  FUN_1000_4068(0xaf32,200);
  FUN_1000_3f75(0x5182,0xfa);
  for (local_8 = 0; local_8 < 10; local_8 = local_8 + 1) {
    FUN_1000_4068(local_8 * 8 + 0x44d0,0xfa);
  }
  FUN_1000_4120();
  FUN_1000_4293(0xaf32);
  FUN_1000_4ae2();
  FUN_1000_4aaf(0,1);
  FUN_1000_4b72(0x5182,1,0x24);
  while( true ) {
    while( true ) {
      if (local_4 != local_6) {
        FUN_1000_4aaf(local_6,0xff);
        local_6 = local_4;
        FUN_1000_4aaf(local_4,1);
      }
      iVar1 = FUN_1000_5fad();
      if (iVar1 != 0xd) break;
      if (local_4 < 3) {
        *(uint *)0x4526 = local_4;
      }
      else {
        *(int *)0x4528 = local_4 - 3;
      }
      if (*(int *)0x4528 == 0) {
        FUN_1000_57a8(1);
      }
      else {
        FUN_1000_5889();
        *(undefined2 *)0xbc2 = 0xffff;
      }
      FUN_1000_4ae2();
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
  FUN_1000_3f1f();
  FUN_1000_5770();
  return;
}


// ---- FUN_1000_4dac @ 1000:4dac ----

bool __cdecl16near FUN_1000_4dac(void)

{
  int iVar1;
  undefined1 local_a [8];
  
  FUN_1000_3f04();
  FUN_1000_3f75(0x5182,200);
  FUN_1000_4068(local_a,200);
  FUN_1000_4293(local_a);
  FUN_1000_4b72(0x5182,1,0x24);
  FUN_1000_3f1f();
  iVar1 = FUN_1000_5fad();
  FUN_1000_4b72(0x5182,0,0x24);
  return iVar1 != 0x1b;
}


// ---- FUN_1000_4e12 @ 1000:4e12 ----

void __cdecl16near FUN_1000_4e12(void)

{
  int iVar1;
  
  FUN_1000_40ff(0xd88);
  iVar1 = FUN_1000_4dac();
  if (iVar1 != 0) {
    FUN_1000_4dac();
  }
  FUN_1000_4120();
  return;
}


// ---- FUN_1000_4e36 @ 1000:4e36 ----

void __cdecl16near FUN_1000_4e36(int param_1)

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
  
  FUN_1000_3f04();
  FUN_1000_57a8(1);
  FUN_1000_40ff(0xd96);
  FUN_1000_3f75(0x5182,0xbe);
  for (uVar2 = 0; uVar2 < 3; uVar2 = uVar2 + 1) {
    FUN_1000_4068(local_1a + uVar2 * 8,0xbe);
  }
  FUN_1000_4120();
  FUN_1000_40ff(0xda4);
  FUN_1000_3f75(0x5182,0);
  FUN_1000_4068(local_22,0);
  FUN_1000_3f04();
  FUN_1000_3f75(0x5182,0x32);
  FUN_1000_3f75(0x5182,0x32);
  FUN_1000_4068(local_2a,0x32);
  FUN_1000_3fc6(local_38,0xa0);
  FUN_1000_3fc6(local_3e,0xa0);
  FUN_1000_4068(local_32,0xa0);
  FUN_1000_4120();
  FUN_1000_4162(local_22[0],local_22[0],1,0);
  FUN_1000_41e5(local_2a);
  FUN_1000_3c7e();
  if ((*(int *)0x36 != 0) && (param_1 == 0)) {
    FUN_1000_6233(0xbe,3,0x53bc);
  }
  if (param_1 != 0) {
    FUN_1000_4293(local_22);
    FUN_1000_4b72(0x5182,1,0x24);
  }
  FUN_1000_4260(local_38);
  FUN_1000_4162(0,0xa000,0,1);
  if (*(int *)0x36 != 0) {
    FUN_1000_41e5(local_32);
    FUN_1000_4315(local_38,local_3e,0x32);
  }
  FUN_1000_3f1f();
  uVar2 = 0;
  do {
    while( true ) {
      FUN_1000_4162(local_22[0],0xa000,1,0);
      FUN_1000_41e5(local_1a + uVar2 * 8);
      iVar1 = FUN_1000_5fad();
      if (iVar1 != 0xd) break;
LAB_1000_4fe7:
      FUN_1000_4b72(0x5182,0,0x24);
      if (uVar2 == 0) {
        FUN_1000_3f1f();
        return;
      }
      if (uVar2 == 1) {
        FUN_1000_4c04();
        FUN_1000_4b72(0x5182,0,0x24);
      }
      else {
        FUN_1000_4e12();
      }
      FUN_1000_4293(local_22);
      FUN_1000_4b72(0x5182,1,0x24);
    }
    if (iVar1 == 0x1b) {
      FUN_1000_0046();
      goto LAB_1000_4fe7;
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


// ---- FUN_1000_5064 @ 1000:5064 ----

void __cdecl16near FUN_1000_5064(uint param_1,int param_2,undefined2 param_3)

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
  
  FUN_1000_3f04();
  local_4 = FUN_1000_3ed8(0x1b0,0);
  local_6 = 0;
  FUN_1000_0069();
  if (*(int *)0x36 == 0) {
    uVar1 = 0xc;
  }
  else {
    uVar1 = 1;
  }
  FUN_1000_5c92(local_6,local_4,uVar1,0x1b0);
  for (local_10 = 0x31; local_10 < 0x180; local_10 = local_10 + 0x30) {
    FUN_1000_5c92(local_6 + local_10,local_4,0,0x2e);
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
  FUN_1000_4162(param_3,0xa000,uVar1,1);
  FUN_1000_41e5(&local_e);
  FUN_1000_3f1f();
  return;
}


// ---- FUN_1000_5164 @ 1000:5164 ----

undefined2 __cdecl16near FUN_1000_5164(void)

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
  FUN_1000_3f04();
  FUN_1000_57a8(1);
  FUN_1000_40ff(0xdae);
  FUN_1000_3f75(0x5182,0);
  FUN_1000_4068(local_a,0);
  FUN_1000_3f75(0x5182,0xf0);
  FUN_1000_4068(local_12,0xf0);
  FUN_1000_4120();
  FUN_1000_3c7e();
  FUN_1000_4162(0,local_a[0],0,0);
  for (uVar2 = 0; uVar2 < 0x1e; uVar2 = uVar2 + 1) {
    iVar1 = (int)(((ulong)uVar2 % 0xf) / 3) * 0x30c0 + (int)(((ulong)uVar2 % 0xf) % 3) * 0xb40;
    local_10 = iVar1 + 0x11f0;
    if (0xe < uVar2) {
      local_10 = iVar1 + 0x1290;
    }
    for (uVar3 = 0; (uVar3 < *(uint *)(uVar2 * 2 + 0x452a) && (uVar3 < 7)); uVar3 = uVar3 + 1) {
      FUN_1000_41e5(local_12);
      local_10 = local_10 + 7;
    }
  }
  FUN_1000_4293(local_a);
  FUN_1000_4b72(0x5182,1,0x24);
  while( true ) {
    if (0x1d < *(uint *)0x933e) {
      *(undefined2 *)0x933e = 0x1d;
    }
    if (*(uint *)0x933e != local_1e) {
      if (local_1e < 1000) {
        FUN_1000_5064(local_1e,0,local_a[0]);
      }
      local_1e = *(uint *)0x933e;
      FUN_1000_5064(local_1e,1,local_a[0]);
    }
    iVar1 = FUN_1000_5fad();
    if (iVar1 == 0xd) break;
    if (iVar1 == 0x1b) {
      local_20 = 1;
LAB_1000_5351:
      FUN_1000_4b72(0x5182,0,0x24);
      FUN_1000_3f1f();
      return local_20;
    }
    if (iVar1 == 0x4800) {
      if (*(int *)0x933e != 0) {
        *(int *)0x933e = *(int *)0x933e + -1;
      }
    }
    else if (iVar1 == 0x4b00) {
      if (*(uint *)0x933e < 0xf) {
        *(undefined2 *)0x933e = 0;
      }
      else {
        *(int *)0x933e = *(int *)0x933e + -0xf;
      }
    }
    else if (iVar1 == 0x4d00) {
      *(int *)0x933e = *(int *)0x933e + 0xf;
    }
    else if (iVar1 == 0x5000) {
      *(int *)0x933e = *(int *)0x933e + 1;
    }
  }
  local_20 = 0;
  goto LAB_1000_5351;
}


// ---- FUN_1000_536b @ 1000:536b ----

void __cdecl16near FUN_1000_536b(undefined2 param_1)

{
  uint uVar1;
  undefined2 unaff_DS;
  undefined1 local_34 [5];
  undefined1 local_2f [37];
  undefined2 local_a [4];
  
  FUN_1000_5cf4(local_34,0xdba);
  FUN_1000_5f14(local_2f,param_1);
  FUN_1000_5eb8(local_34,0xdc0);
  FUN_1000_40ff(local_34);
  FUN_1000_3f75(0x41d0,0x8e);
  FUN_1000_4068(local_a,0x8e);
  FUN_1000_4120();
  *(undefined2 *)0x517e = local_a[0];
  FUN_1000_5c57(local_a[0],4000);
  if (*(int *)0x41b6 == 0) {
    FUN_1000_5c92(0xac80,local_a[0],0,0x4d80);
    FUN_1000_4162(*(undefined2 *)0x517e,*(undefined2 *)0x517e,0,1);
    *(undefined2 *)0x961e = 0x140;
    *(undefined2 *)0x4522 = *(undefined2 *)0x54a4;
    for (uVar1 = 0; uVar1 < 0x58c0; uVar1 = uVar1 + 0x140) {
      FUN_1000_4184(uVar1 + 0xa140,uVar1,0,0);
    }
    if (*(int *)0x36 == 0) {
      FUN_1000_3c95(*(undefined2 *)0x517e,0,2,0x140,200);
      *(undefined2 *)0x517e = 0xa400;
    }
  }
  return;
}


// ---- FUN_1000_5465 @ 1000:5465 ----

void __cdecl16near
FUN_1000_5465(undefined2 param_1,undefined2 param_2,int param_3,undefined2 *param_4)

{
  undefined2 uVar1;
  int iVar2;
  undefined2 uVar3;
  undefined2 unaff_DS;
  
  uVar1 = FUN_1000_5c38(param_1);
  iVar2 = FUN_1000_5c67(uVar1,0,0,2);
  iVar2 = iVar2 + param_3 * -2;
  FUN_1000_60b0(uVar1);
  uVar3 = FUN_1000_3ed8(iVar2,0);
  param_4[1] = uVar3;
  *param_4 = 0;
  FUN_1000_0069();
  FUN_1000_5f3f(uVar1,param_2,param_3 << 1);
  FUN_1000_5f77(uVar1,*param_4,param_4[1],iVar2);
  FUN_1000_5c1a(uVar1);
  return;
}


// ---- FUN_1000_54ec @ 1000:54ec ----

void __cdecl16near FUN_1000_54ec(void)

{
  undefined2 uVar1;
  
  FUN_1000_5465(0xdc6,0x9604,10,0x5482);
  FUN_1000_5465(0xdd4,0x548c,10,0x961a);
  FUN_1000_5465(0xde2,0x4580,0x22,0x54b0);
  uVar1 = FUN_1000_5c38(0xdec);
  FUN_1000_5f3f(uVar1,0x962e,0x18fe);
  FUN_1000_5bf5();
  FUN_1000_5c1a(uVar1);
  return;
}


// ---- FUN_1000_554b @ 1000:554b ----

void __cdecl16near FUN_1000_554b(void)

{
  undefined2 uVar1;
  undefined2 unaff_DS;
  undefined2 local_a [4];
  
  FUN_1000_40ff(0xdf6);
  FUN_1000_3f75(0x41d0,0x48);
  FUN_1000_4068(local_a,0x48);
  *(undefined2 *)0xaf46 = local_a[0];
  *(undefined2 *)0xaf44 = 0;
  FUN_1000_4120();
  FUN_1000_40ff(0xe00);
  FUN_1000_3f75(0x41d0,0x5c);
  if (*(int *)0x36 == 0) {
    FUN_1000_3f04();
  }
  FUN_1000_4068(0x54a4,0x5c);
  if (*(int *)0x36 == 0) {
    FUN_1000_3f1f();
    FUN_1000_4068(0x54a4,0x5c);
  }
  FUN_1000_4120();
  uVar1 = FUN_1000_5c38(0xe0c,0,*(undefined2 *)0x456c,0x7d64);
  *(undefined2 *)0x41b8 = uVar1;
  FUN_1000_5f77(uVar1);
  FUN_1000_5bf5();
  FUN_1000_4120();
  return;
}


// ---- FUN_1000_55f8 @ 1000:55f8 ----

uint __cdecl16near FUN_1000_55f8(int param_1)

{
  undefined2 uVar1;
  undefined2 unaff_DS;
  undefined2 local_8;
  uint local_6;
  undefined2 local_4;
  
  FUN_1000_5cc8(0x1638,0,7000);
  local_4 = FUN_1000_5c38(0xe14);
  FUN_1000_5c67(local_4,param_1 << 2,0,0);
  FUN_1000_5f3f(local_4,&local_8,2);
  FUN_1000_5f3f(local_4,&local_6,2);
  FUN_1000_5c67(local_4,local_8,0,0);
  FUN_1000_639a(local_4,0,0x1000,0);
  uVar1 = FUN_1000_64f0();
  *(undefined2 *)0x456e = uVar1;
  uVar1 = FUN_1000_64f0();
  *(undefined2 *)0x54ae = uVar1;
  uVar1 = FUN_1000_64f0();
  *(undefined2 *)0x4574 = uVar1;
  FUN_1000_650f(0x41d0);
  FUN_1000_6660(0x1638);
  FUN_1000_5c1a(local_4);
  return local_6 / 0xe;
}


// ---- FUN_1000_56c3 @ 1000:56c3 ----

bool __cdecl16near FUN_1000_56c3(void)

{
  int iVar1;
  undefined2 unaff_DS;
  uint local_8;
  int local_6;
  
  local_6 = 0;
  for (local_8 = 1; local_8 < 0x21; local_8 = local_8 + 1) {
    local_6 = local_6 + (*(uint *)0x4526 ^ local_8);
  }
  iVar1 = *(int *)0x4524;
  if (local_6 != iVar1) {
    *(int *)0x4524 = local_6;
  }
  return local_6 != iVar1;
}


// ---- FUN_1000_571b @ 1000:571b ----

void __cdecl16near FUN_1000_571b(void)

{
  undefined2 uVar1;
  int iVar2;
  undefined2 unaff_DS;
  
  uVar1 = FUN_1000_5c38(0xbcc);
  FUN_1000_5f3f(uVar1,0x4524,0x42);
  FUN_1000_5c1a(uVar1);
  if ((*(int *)0x41b6 != 0) || (iVar2 = FUN_1000_56c3(), iVar2 != 0)) {
    FUN_1000_5cc8(0x4524,0,0x42);
  }
  *(undefined2 *)0x41b6 = 0;
  return;
}


// ---- FUN_1000_5770 @ 1000:5770 ----

void __cdecl16near FUN_1000_5770(void)

{
  undefined2 uVar1;
  undefined2 unaff_DS;
  
  FUN_1000_56c3();
  uVar1 = FUN_1000_5c2b(0xbcc,0);
  FUN_1000_606d(uVar1,0x4524,0x42);
  FUN_1000_5c1a(uVar1);
  *(undefined2 *)0x41b6 = 0;
  return;
}


// ---- FUN_1000_57a8 @ 1000:57a8 ----

void __cdecl16near FUN_1000_57a8(int param_1)

{
  undefined2 uVar1;
  undefined2 unaff_DS;
  undefined2 local_8;
  int local_6;
  uint local_4;
  
  if ((*(int *)0xbc2 != param_1) && (FUN_1000_5889(), *(int *)0x4528 == 0)) {
    uVar1 = FUN_1000_5c38(0xe1e);
    *(undefined2 *)0x41b8 = uVar1;
    FUN_1000_5c67(*(undefined2 *)0x41b8,param_1 * 6,0,0);
    FUN_1000_5f3f(*(undefined2 *)0x41b8,&local_8,6);
    FUN_1000_5c67(*(undefined2 *)0x41b8,local_8,0,0);
    FUN_1000_639a(*(undefined2 *)0x41b8,0,0x1000,0);
    if (local_4 < 16000) {
      FUN_1000_6660(0x54bc);
    }
    else {
      FUN_1000_5c0a(0xff);
    }
    FUN_1000_4120();
    if (*(int *)0x41b6 == 0) {
      FUN_1000_5a61(local_6 * 0x10 + 0x54bc,0x54bc);
      *(int *)0xbc2 = param_1;
    }
  }
  return;
}


// ---- FUN_1000_5876 @ 1000:5876 ----

undefined1 __cdecl16near FUN_1000_5876(void)

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


// ---- FUN_1000_5889 @ 1000:5889 ----

void __cdecl16near FUN_1000_5889(void)

{
  byte bVar1;
  char cVar2;
  undefined2 unaff_DS;
  
  *(undefined2 *)0x31a2 = 0xcbc;
  *(undefined1 *)0x31a6 = 0xe0;
  bVar1 = 0x40;
  do {
    FUN_1000_5876();
    bVar1 = bVar1 + 1;
  } while (bVar1 < 0x56);
  cVar2 = '\a';
  do {
    FUN_1000_59b3();
    cVar2 = cVar2 + -1;
  } while (-1 < cVar2);
  return;
}


// ---- FUN_1000_58b1 @ 1000:58b1 ----

void __cdecl16near FUN_1000_58b1(void)

{
  byte bVar1;
  undefined2 unaff_DS;
  
  FUN_1000_5889();
  FUN_1000_5876();
  FUN_1000_5876();
  FUN_1000_5876();
  *(undefined2 *)0x31a0 = 0xc90;
  bVar1 = 7;
  do {
    FUN_1000_58fd();
    *(int *)0x31a0 = *(int *)0x31a0 + 0xb;
    bVar1 = bVar1 + 1;
  } while (bVar1 < 0xb);
  FUN_1000_5876();
  FUN_1000_5876();
  FUN_1000_5876();
  FUN_1000_5876();
  return;
}


// ---- FUN_1000_58fd @ 1000:58fd ----

void __cdecl16near FUN_1000_58fd(void)

{
  uint in_AX;
  uint uVar1;
  uint uVar2;
  undefined2 unaff_DS;
  
  FUN_1000_59b3();
  uVar2 = in_AX & 0xff;
  *(undefined1 *)(uVar2 + 0x31a7) = (char)(in_AX >> 8);
  uVar1 = 0;
  do {
    FUN_1000_5876();
    uVar1 = uVar1 + 1;
  } while (uVar1 < 5);
  do {
    if (!CARRY1(*(byte *)(uVar2 + 0xc32),*(byte *)(uVar1 + 0xc1c))) {
      FUN_1000_5876();
    }
    uVar1 = uVar1 + 1;
  } while (uVar1 < 10);
  if (*(char *)(uVar2 + 0xc3d) != -1) {
    FUN_1000_5876();
  }
  return;
}


// ---- FUN_1000_59b3 @ 1000:59b3 ----

void FUN_1000_59b3(void)

{
  byte bVar1;
  byte in_AL;
  undefined2 unaff_DS;
  
  if (5 < in_AL) {
    bVar1 = in_AL - 6 & 7;
    *(byte *)0x31a6 = (0xefU >> bVar1 | -0x11 << 8 - bVar1) & *(byte *)0x31a6;
  }
  FUN_1000_5876();
  return;
}


// ---- FUN_1000_5a61 @ 1000:5a61 ----

void __cdecl16near FUN_1000_5a61(undefined2 param_1,undefined2 param_2)

{
  undefined2 unaff_DS;
  
  *(undefined2 *)0x31a2 = param_1;
  *(undefined2 *)0x31a4 = param_1;
  *(undefined2 *)0x31a0 = param_2;
  *(undefined1 *)0x31b2 = 0;
  return;
}


// ---- FUN_1000_5a7c @ 1000:5a7c ----

undefined2 __cdecl16near FUN_1000_5a7c(void)

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
    out(*(int *)0xcc2 + 6,1);
    out(0x43,0);
    uVar1 = in(0x40);
    uVar2 = in(0x40);
    do {
      out(0x43,0);
      uVar3 = in(0x40);
      uVar4 = in(0x40);
    } while ((uint)-(CONCAT11(uVar4,uVar3) - CONCAT11(uVar2,uVar1)) < 8);
    out(*(int *)0xcc2 + 6,0);
    out(0x43,0);
    uVar1 = in(0x40);
    uVar2 = in(0x40);
    in_AX = in_AX & 0xff00;
    do {
      bVar6 = (byte)(in_AX >> 8);
      cVar5 = in(*(int *)0xcc2 + 0xe);
      if ((cVar5 < '\0') && (cVar5 = in(*(int *)0xcc2 + 10), cVar5 == -0x56)) {
        do {
          cVar5 = in(*(int *)0xcc2 + 0xc);
        } while (cVar5 < '\0');
        out(*(int *)0xcc2 + 0xc,0xd1);
        return CONCAT11(bVar6,0xd1);
      }
      out(0x43,0);
      uVar3 = in(0x40);
      uVar4 = in(0x40);
      in_AX = (uint)bVar6 << 8;
    } while ((uint)-(CONCAT11(uVar4,uVar3) - CONCAT11(uVar2,uVar1)) < 0xf0);
    *(int *)0xcc2 = *(int *)0xcc2 + 0x10;
    if (0x260 < *(uint *)0xcc2) {
      *(undefined2 *)0xcc2 = 0;
      return 0;
    }
  } while( true );
}


// ---- FUN_1000_5b1d @ 1000:5b1d ----

undefined4 __cdecl16near FUN_1000_5b1d(void)

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
  
  bVar1 = (byte)*(undefined2 *)0xcc4 | 4;
  out(10,bVar1);
  out(0xb,bVar1 ^ 0x5c);
  out(0xc,0);
  iVar2 = in_BX * 0x10 + in_DX;
  iVar4 = *(int *)0xcc4 * 2;
  out(iVar4,(char)iVar2);
  uVar3 = (undefined1)((uint)iVar2 >> 8);
  out(iVar4,uVar3);
  iVar4 = iVar4 + 1;
  out(iVar4,in_CL);
  out(iVar4,in_CH);
  uVar5 = CONCAT11((char)((uint)iVar4 >> 8),*(undefined1 *)(*(int *)0xcc4 + 0xcc6));
  out(uVar5,(byte)((uint)in_BX >> 0xc) + CARRY2(in_BX * 0x10,in_DX));
  out(10,1);
  return CONCAT22(uVar5,CONCAT11(uVar3,1));
}


// ---- FUN_1000_5b5a @ 1000:5b5a ----

void __cdecl16near
FUN_1000_5b5a(undefined2 param_1,undefined2 param_2,undefined1 param_3,int param_4)

{
  char cVar1;
  int iVar2;
  undefined2 unaff_DS;
  
  if (*(int *)0xcc2 != 0) {
    param_4 = param_4 + -1;
    FUN_1000_5b1d();
    iVar2 = *(int *)0xcc2 + 0xc;
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


// ---- FUN_1000_5ba4 @ 1000:5ba4 ----

void __cdecl16near FUN_1000_5ba4(void)

{
  char cVar1;
  int iVar2;
  undefined2 unaff_DS;
  
  if (*(int *)0xcc2 != 0) {
    iVar2 = *(int *)0xcc2 + 0xc;
    do {
      cVar1 = in(iVar2);
    } while (cVar1 < '\0');
    out(iVar2,0xd0);
    out(10,(byte)*(undefined2 *)0xcc4 | 4);
  }
  return;
}


// ---- FUN_1000_5bbf @ 1000:5bbf ----

undefined2 __cdecl16near FUN_1000_5bbf(void)

{
  code *pcVar1;
  undefined2 uVar2;
  undefined2 unaff_DS;
  bool bVar3;
  
  bVar3 = false;
  if (*(int *)0x41b6 == 0) {
    pcVar1 = (code *)swi(0x21);
    uVar2 = (*pcVar1)();
    if (!bVar3) {
      return 0;
    }
    if (*(int *)0x41b6 == 0) {
      *(undefined2 *)0x41b6 = uVar2;
    }
  }
  return 0xffff;
}


// ---- FUN_1000_5bdc @ 1000:5bdc ----

undefined2 __cdecl16near FUN_1000_5bdc(void)

{
  code *pcVar1;
  undefined2 uVar2;
  undefined2 unaff_DS;
  bool bVar3;
  
  bVar3 = false;
  if (*(int *)0x41b6 == 0) {
    pcVar1 = (code *)swi(0x21);
    uVar2 = (*pcVar1)();
    if (!bVar3) {
      return uVar2;
    }
    if (*(int *)0x41b6 == 0) {
      *(undefined2 *)0x41b6 = uVar2;
    }
  }
  return 0xffff;
}


// ---- FUN_1000_5bf5 @ 1000:5bf5 ----

void __cdecl16near FUN_1000_5bf5(void)

{
  undefined2 unaff_DS;
  
  if ((*(int *)0x41b6 == 0x12) || (*(int *)0x41b6 == 0x14)) {
    *(undefined2 *)0x41b6 = 0;
  }
  return;
}


// ---- FUN_1000_5c0a @ 1000:5c0a ----

void __cdecl16near FUN_1000_5c0a(undefined2 param_1)

{
  undefined2 unaff_DS;
  
  if (*(int *)0x41b6 == 0) {
    *(undefined2 *)0x41b6 = param_1;
  }
  return;
}


// ---- FUN_1000_5c1a @ 1000:5c1a ----

void __cdecl16near FUN_1000_5c1a(void)

{
  code *pcVar1;
  undefined2 unaff_DS;
  
  if (*(int *)0x41b6 != 0x15) {
    pcVar1 = (code *)swi(0x21);
    (*pcVar1)();
  }
  return;
}


// ---- FUN_1000_5c2b @ 1000:5c2b ----

void FUN_1000_5c2b(void)

{
  FUN_1000_5bdc();
  return;
}


// ---- FUN_1000_5c38 @ 1000:5c38 ----

void FUN_1000_5c38(void)

{
  FUN_1000_5bdc();
  return;
}


// ---- FUN_1000_5c43 @ 1000:5c43 ----

void __cdecl16near FUN_1000_5c43(char *param_1)

{
  char *pcVar1;
  undefined2 unaff_DS;
  
  while( true ) {
    pcVar1 = param_1;
    param_1 = param_1 + 1;
    if (*pcVar1 == '\0') break;
    FUN_1000_5f96(*pcVar1);
  }
  return;
}


// ---- FUN_1000_5c57 @ 1000:5c57 ----

void __cdecl16near FUN_1000_5c57(void)

{
  FUN_1000_5bbf();
  return;
}


// ---- FUN_1000_5c67 @ 1000:5c67 ----

void __cdecl16near FUN_1000_5c67(void)

{
  code *pcVar1;
  undefined2 uVar2;
  undefined2 unaff_DS;
  bool bVar3;
  
  bVar3 = false;
  if (*(int *)0x41b6 == 0) {
    pcVar1 = (code *)swi(0x21);
    uVar2 = (*pcVar1)();
    if ((bVar3) && (*(int *)0x41b6 == 0)) {
      *(undefined2 *)0x41b6 = uVar2;
    }
  }
  return;
}


// ---- FUN_1000_5c92 @ 1000:5c92 ----

void __cdecl16near FUN_1000_5c92(undefined1 *param_1,undefined1 param_2,int param_3)

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


// ---- FUN_1000_5ca4 @ 1000:5ca4 ----

void __cdecl16near FUN_1000_5ca4(undefined1 *param_1,undefined1 *param_2,int param_3)

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


// ---- FUN_1000_5cc8 @ 1000:5cc8 ----

void __cdecl16near FUN_1000_5cc8(undefined1 *param_1,undefined1 param_2,int param_3)

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


// ---- FUN_1000_5cdc @ 1000:5cdc ----

char * __cdecl16near FUN_1000_5cdc(int param_1,char param_2)

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


// ---- FUN_1000_5cf4 @ 1000:5cf4 ----

void __cdecl16near FUN_1000_5cf4(char *param_1,char *param_2)

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


// ---- FUN_1000_5d0e @ 1000:5d0e ----

long FUN_1000_5d0e(uint param_1,int param_2,uint param_3,int param_4)

{
  if (param_4 == 0 && param_2 == 0) {
    return (ulong)param_1 * (ulong)param_3;
  }
  return CONCAT22((int)((ulong)param_1 * (ulong)param_3 >> 0x10) +
                  param_2 * param_3 + param_1 * param_4,(int)((ulong)param_1 * (ulong)param_3));
}


// ---- FUN_1000_5d42 @ 1000:5d42 ----

void __cdecl16near FUN_1000_5d42(void)

{
  uint in_CX;
  uint uVar1;
  
  for (uVar1 = in_CX & 0xff; uVar1 != 0; uVar1 = uVar1 - 1) {
  }
  return;
}


// ---- FUN_1000_5d4e @ 1000:5d4e ----

undefined4 FUN_1000_5d4e(uint param_1,uint param_2,uint param_3,uint param_4)

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


// ---- FUN_1000_5db0 @ 1000:5db0 ----

undefined4 FUN_1000_5db0(uint param_1,uint param_2,uint param_3,uint param_4)

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


// ---- FUN_1000_5e1c @ 1000:5e1c ----

undefined4 FUN_1000_5e1c(uint param_1,uint param_2,uint param_3,uint param_4)

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


// ---- FUN_1000_5eb8 @ 1000:5eb8 ----

void __cdecl16near FUN_1000_5eb8(undefined2 param_1,undefined2 param_2)

{
  undefined2 uVar1;
  
  uVar1 = FUN_1000_5cdc(param_1,0,param_2);
  FUN_1000_5cf4(uVar1);
  return;
}


// ---- FUN_1000_5ece @ 1000:5ece ----

void __cdecl16near FUN_1000_5ece(int param_1,undefined2 param_2,undefined2 param_3)

{
  char cVar1;
  char *pcVar2;
  undefined2 unaff_DS;
  long lVar3;
  
  lVar3 = CONCAT22(param_3,param_2);
  pcVar2 = (char *)(param_1 + 10);
  *pcVar2 = '\0';
  do {
    cVar1 = FUN_1000_5db0(lVar3,10,0);
    pcVar2 = pcVar2 + -1;
    *pcVar2 = cVar1 + '0';
    lVar3 = FUN_1000_5d4e(lVar3,10,0);
  } while (lVar3 != 0);
  FUN_1000_5cf4(param_1,pcVar2);
  return;
}


// ---- FUN_1000_5f14 @ 1000:5f14 ----

void __cdecl16near FUN_1000_5f14(int param_1,uint param_2)

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
  FUN_1000_5cf4(param_1,pcVar2);
  return;
}


// ---- FUN_1000_5f3f @ 1000:5f3f ----

int __cdecl16near FUN_1000_5f3f(undefined2 param_1,undefined2 param_2,int param_3)

{
  code *pcVar1;
  int iVar2;
  undefined2 unaff_SS;
  bool bVar3;
  
  bVar3 = false;
  if (*(int *)0x41b6 == 0) {
    pcVar1 = (code *)swi(0x21);
    iVar2 = (*pcVar1)();
    if (!bVar3) {
      if (iVar2 == param_3) {
        return iVar2;
      }
      *(undefined2 *)0x41b6 = 0x14;
      return iVar2;
    }
    if (*(int *)0x41b6 == 0) {
      *(int *)0x41b6 = iVar2;
    }
  }
  return -1;
}


// ---- FUN_1000_5f77 @ 1000:5f77 ----

void __cdecl16near
FUN_1000_5f77(undefined2 param_1,undefined2 param_2,undefined2 param_3,undefined2 param_4)

{
  FUN_1000_5f3f(param_1,param_2,param_4);
  return;
}


// ---- FUN_1000_5f8e @ 1000:5f8e ----

uint __cdecl16near FUN_1000_5f8e(void)

{
  code *pcVar1;
  uint uVar2;
  
  pcVar1 = (code *)swi(0x21);
  uVar2 = (*pcVar1)();
  return uVar2 & 1;
}


// ---- FUN_1000_5f96 @ 1000:5f96 ----

void __cdecl16near FUN_1000_5f96(char param_1)

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


// ---- FUN_1000_5fad @ 1000:5fad ----

uint __cdecl16near FUN_1000_5fad(void)

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


// ---- FUN_1000_5fc3 @ 1000:5fc3 ----

void FUN_1000_5fc3(void)

{
  code *pcVar1;
  
  pcVar1 = (code *)swi(0x21);
  (*pcVar1)();
  FUN_1000_5ece();
  FUN_1000_5c43();
  return;
}


// ---- FUN_1000_5fc8 @ 1000:5fc8 ----

void __cdecl16near FUN_1000_5fc8(void)

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


// ---- FUN_1000_5fdf @ 1000:5fdf ----

void __cdecl16near FUN_1000_5fdf(void)

{
  code *pcVar1;
  
  pcVar1 = (code *)swi(0x10);
  (*pcVar1)();
  return;
}


// ---- FUN_1000_5fe9 @ 1000:5fe9 ----

undefined2 __cdecl16near FUN_1000_5fe9(void)

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


// ---- FUN_1000_5ffd @ 1000:5ffd ----

undefined2 __cdecl16near FUN_1000_5ffd(void)

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


// ---- FUN_1000_6015 @ 1000:6015 ----

undefined1 * __cdecl16near FUN_1000_6015(undefined1 *param_1,undefined1 *param_2,int param_3)

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


// ---- FUN_1000_6061 @ 1000:6061 ----

void __cdecl16near FUN_1000_6061(void)

{
  code *pcVar1;
  
  pcVar1 = (code *)swi(0x21);
  (*pcVar1)();
  return;
}


// ---- FUN_1000_606d @ 1000:606d ----

int __cdecl16near FUN_1000_606d(undefined2 param_1,undefined2 param_2,int param_3)

{
  code *pcVar1;
  int iVar2;
  undefined2 unaff_SS;
  bool bVar3;
  
  if (*(int *)0x41b6 == 0) {
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
      *(undefined2 *)0x41b6 = 0x13;
      return iVar2;
    }
    if (*(int *)0x41b6 == 0) {
      *(int *)0x41b6 = iVar2;
    }
  }
  return -1;
}


// ---- FUN_1000_60ab @ 1000:60ab ----

void FUN_1000_60ab(undefined2 param_1)

{
  FUN_1000_5fc3(1);
  FUN_1000_5c67(param_1,0,0,0);
  return;
}


// ---- FUN_1000_60b0 @ 1000:60b0 ----

void __cdecl16near FUN_1000_60b0(undefined2 param_1)

{
  FUN_1000_5c67(param_1,0,0,0);
  return;
}


// ---- FUN_1000_60c1 @ 1000:60c1 ----

void __cdecl16near FUN_1000_60c1(void)

{
  code *pcVar1;
  
  pcVar1 = (code *)swi(0x10);
  (*pcVar1)();
  return;
}


// ---- entry @ 1000:60d0 ----

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
  DAT_166e_0ccc = unaff_ES;
  uVar6 = (*pcVar5)();
  DAT_166e_0cca = CONCAT11((byte)uVar6,(char)((uint)uVar6 >> 8));
  if (2 < (byte)uVar6) {
    if (DAT_166e_0cca >> 1 != 0) {
      puVar11 = puVar10 + -0x4eb0;
      pcVar5 = (code *)swi(0x21);
      (*pcVar5)();
      uVar6 = *(undefined2 *)0x2c;
      pcVar14 = (char *)0x0;
      iVar7 = -0x8000;
code_r0x0001612b:
      do {
        pcVar16 = pcVar14;
        if (iVar7 != 0) {
          iVar7 = iVar7 + -1;
          pcVar2 = pcVar14;
          pcVar14 = pcVar14 + 1;
          pcVar16 = pcVar14;
          if (*pcVar2 != '\0') goto code_r0x0001612b;
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
      *(undefined2 *)(puVar11 + iVar7 + -2) = 0x166e;
      uVar19 = *(undefined2 *)(puVar11 + iVar7 + -2);
      for (; iVar15 != 0; iVar15 = iVar15 + -1) {
        pcVar3 = pcVar14;
        pcVar14 = pcVar14 + 1;
        pcVar2 = pcVar16;
        pcVar16 = pcVar16 + 1;
        *pcVar3 = *pcVar2;
      }
      *(undefined2 *)(puVar11 + iVar7 + -2) = 0x166e;
      uVar6 = *(undefined2 *)0xccc;
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
        *(undefined2 *)(pcVar16 + -2) = 0x166e;
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
            if ((cVar1 == '\r') || (cVar1 == '\0')) goto LAB_1000_61a3;
          } while ((cVar1 != ' ') && (cVar1 != '\t'));
          *pcVar17 = '\0';
        }
LAB_1000_61a3:
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
      *(undefined2 *)(pcVar16 + -8) = 0x166e;
      uVar6 = *(undefined2 *)(pcVar16 + -8);
      puVar18 = (undefined1 *)0xe28;
      for (iVar7 = -0x5cd8; iVar7 != 0; iVar7 = iVar7 + -1) {
        puVar4 = puVar18;
        puVar18 = puVar18 + 1;
        *puVar4 = 0;
      }
      *(undefined2 *)(pcVar16 + -8) = 0x61e8;
      FUN_1000_01b8();
      pcVar5 = (code *)swi(0x21);
      (*pcVar5)();
      *(undefined2 *)(pcVar13 + -2) = *(undefined2 *)(pcVar13 + 4);
      *(undefined2 *)(pcVar13 + -4) = *(undefined2 *)(pcVar13 + 2);
      *(undefined2 *)(pcVar13 + -6) = 1;
      *(undefined2 *)(pcVar13 + -8) = 0x61fa;
      uVar6 = FUN_1000_5ece();
      *(undefined2 *)(pcVar13 + -8) = uVar6;
      *(undefined2 *)(pcVar13 + -10) = 0x61fe;
      FUN_1000_5c43();
      return;
    }
    pcVar5 = (code *)swi(0x21);
    (*pcVar5)();
  }
  *(undefined2 *)(puVar10 + -2) = unaff_ES;
  *(undefined2 *)(puVar10 + -4) = 0;
  return;
}


// ---- FUN_1000_61ec @ 1000:61ec ----

void __cdecl16near FUN_1000_61ec(undefined2 param_1,undefined2 param_2)

{
  undefined2 uVar1;
  
  uVar1 = FUN_1000_5ece(1,param_1,param_2);
  FUN_1000_5c43(uVar1);
  return;
}


// ---- FUN_1000_6202 @ 1000:6202 ----

undefined2 __cdecl16near FUN_1000_6202(void)

{
  code *pcVar1;
  undefined2 uVar2;
  undefined2 unaff_DS;
  bool bVar3;
  
  bVar3 = false;
  if (*(int *)0x41b6 == 0) {
    pcVar1 = (code *)swi(0x21);
    uVar2 = (*pcVar1)();
    if (!bVar3) {
      return uVar2;
    }
    *(undefined2 *)0x41b6 = uVar2;
  }
  return 0;
}


// ---- FUN_1000_6233 @ 1000:6233 ----

undefined4 __cdecl16near FUN_1000_6233(char param_1,uint param_2,undefined1 *param_3)

{
  code *pcVar1;
  byte bVar2;
  undefined2 in_AX;
  int iVar3;
  undefined2 in_DX;
  undefined1 *puVar4;
  undefined1 *puVar5;
  undefined2 uVar6;
  bool bVar7;
  
  bVar7 = false;
  uVar6 = (undefined2)((ulong)param_3 >> 0x10);
  puVar4 = (undefined1 *)param_3;
  if ((bRam00000489 & 6) == 0) {
    do {
      iVar3 = -1;
      do {
        bVar2 = in(iRam00000463 + 6);
        iVar3 = iVar3 + -1;
      } while (iVar3 != 0 && (bVar2 & 8) == 0);
      do {
        do {
          out(0x3c8,param_1);
          puVar5 = puVar4 + (uint)bVar7 * -2 + 1;
          out(0x3c9,*puVar4);
          out(0x3c9,*puVar5);
          puVar4 = puVar5 + (uint)bVar7 * -2 + 1 + (uint)bVar7 * -2 + 1;
          out(0x3c9,puVar5[(uint)bVar7 * -2 + 1]);
          param_1 = param_1 + '\x01';
          param_2 = param_2 - 1;
        } while ((param_2 & 0x3f) != 0);
        if (param_2 == 0) goto LAB_1000_629c;
        bVar2 = in(iRam00000463 + 6);
      } while ((bVar2 & 8) != 0);
      bVar7 = bVar7 != false;
    } while( true );
  }
  pcVar1 = (code *)swi(0x10);
  (*pcVar1)();
LAB_1000_629c:
  return CONCAT22(in_DX,in_AX);
}


// ---- FUN_1000_62a0 @ 1000:62a0 ----

void __cdecl16near FUN_1000_62a0(void)

{
  undefined1 *puVar1;
  int iVar2;
  undefined2 uVar3;
  int iVar4;
  undefined2 unaff_DS;
  
  if (*(int *)0x41c2 != *(int *)0x41c0) {
    puVar1 = (undefined1 *)*(undefined2 *)0x41c2;
    *(int *)0x41c2 = *(int *)0x41c2 + 1;
    *(undefined1 *)0x41bc = *puVar1;
    return;
  }
  if (*(char *)0x41c7 != '\0') {
    FUN_1000_5c0a(0x14);
    return;
  }
  uVar3 = FUN_1000_634d();
  *(undefined2 *)0x41c4 = uVar3;
  iVar4 = *(int *)0x41c0;
  iVar2 = *(int *)0x41be;
  *(int *)0x41c2 = iVar2;
  iVar4 = FUN_1000_5f3f(*(undefined2 *)0x41b8,iVar2,iVar4 - iVar2);
  if (iVar4 == 0) {
    iVar4 = 1;
    *(undefined1 *)0x41c7 = 1;
  }
  *(int *)0x41c0 = iVar4 + *(int *)0x41be;
  FUN_1000_5bf5();
  puVar1 = (undefined1 *)*(undefined2 *)0x41c2;
  *(int *)0x41c2 = *(int *)0x41c2 + 1;
  *(undefined1 *)0x41bc = *puVar1;
  *(undefined2 *)0x41ba = 8;
  return;
}


// ---- FUN_1000_62b7 @ 1000:62b7 ----

void __cdecl16near FUN_1000_62b7(void)

{
  undefined2 unaff_DS;
  
  if (*(int *)0x41c2 == *(int *)0x41c0) {
    FUN_1000_631d();
    *(undefined2 *)0x41c2 = *(undefined2 *)0x41be;
  }
  return;
}


// ---- FUN_1000_62ca @ 1000:62ca ----

void __cdecl16near FUN_1000_62ca(void)

{
  int iVar1;
  undefined1 *puVar2;
  undefined2 uVar3;
  int iVar4;
  undefined2 unaff_DS;
  
  if (*(char *)0x41c7 != '\0') {
    FUN_1000_5c0a(0x14);
    return;
  }
  uVar3 = FUN_1000_634d();
  *(undefined2 *)0x41c4 = uVar3;
  iVar4 = *(int *)0x41c0;
  iVar1 = *(int *)0x41be;
  *(int *)0x41c2 = iVar1;
  iVar4 = FUN_1000_5f3f(*(undefined2 *)0x41b8,iVar1,iVar4 - iVar1);
  if (iVar4 == 0) {
    iVar4 = 1;
    *(undefined1 *)0x41c7 = 1;
  }
  *(int *)0x41c0 = iVar4 + *(int *)0x41be;
  FUN_1000_5bf5();
  puVar2 = (undefined1 *)*(undefined2 *)0x41c2;
  *(int *)0x41c2 = *(int *)0x41c2 + 1;
  *(undefined1 *)0x41bc = *puVar2;
  *(undefined2 *)0x41ba = 8;
  return;
}


// ---- FUN_1000_62de @ 1000:62de ----

void __cdecl16near FUN_1000_62de(void)

{
  int iVar1;
  undefined1 *puVar2;
  int iVar3;
  undefined2 unaff_DS;
  
  iVar3 = *(int *)0x41c0;
  iVar1 = *(int *)0x41be;
  *(int *)0x41c2 = iVar1;
  iVar3 = FUN_1000_5f3f(*(undefined2 *)0x41b8,iVar1,iVar3 - iVar1);
  if (iVar3 == 0) {
    iVar3 = 1;
    *(undefined1 *)0x41c7 = 1;
  }
  *(int *)0x41c0 = iVar3 + *(int *)0x41be;
  FUN_1000_5bf5();
  puVar2 = (undefined1 *)*(undefined2 *)0x41c2;
  *(int *)0x41c2 = *(int *)0x41c2 + 1;
  *(undefined1 *)0x41bc = *puVar2;
  *(undefined2 *)0x41ba = 8;
  return;
}


// ---- FUN_1000_631d @ 1000:631d ----

void __cdecl16near FUN_1000_631d(void)

{
  undefined2 uVar1;
  undefined2 unaff_DS;
  
  FUN_1000_606d(*(undefined2 *)0x41b8,*(int *)0x41be,*(int *)0x41c2 - *(int *)0x41be);
  uVar1 = FUN_1000_6339();
  *(undefined2 *)0x41c4 = uVar1;
  return;
}


// ---- FUN_1000_6339 @ 1000:6339 ----

void __cdecl16near FUN_1000_6339(void)

{
  int iVar1;
  undefined2 unaff_DS;
  
  iVar1 = *(int *)0x41c2;
  if ((*(char *)0x41c6 == '\0') && (*(int *)0x41ba == 8)) {
    iVar1 = iVar1 + -1;
  }
  if (*(char *)0x41c8 != '\0') {
    FUN_1000_6616(*(int *)0x41be,iVar1 - *(int *)0x41be,*(undefined2 *)0x41c4);
  }
  return;
}


// ---- FUN_1000_634d @ 1000:634d ----

void __cdecl16near FUN_1000_634d(void)

{
  undefined2 unaff_DS;
  
  if (*(char *)0x41c8 != '\0') {
    FUN_1000_6616(*(int *)0x41be,*(int *)0x41c0 - *(int *)0x41be,*(undefined2 *)0x41c4);
  }
  return;
}


// ---- FUN_1000_636a @ 1000:636a ----

void __cdecl16near FUN_1000_636a(int param_1,uint param_2)

{
  uint uVar1;
  int iVar2;
  undefined2 unaff_DS;
  
  iVar2 = param_1 + 0x31b4;
  *(int *)0x41be = iVar2;
  *(int *)0x41c2 = iVar2;
  uVar1 = 0x1000U - param_1;
  if (param_2 <= 0x1000U - param_1) {
    uVar1 = param_2;
  }
  *(int *)0x41c0 = uVar1 + iVar2;
  *(undefined2 *)0x41c4 = 0;
  return;
}


// ---- FUN_1000_639a @ 1000:639a ----

void __cdecl16near
FUN_1000_639a(undefined2 param_1,undefined2 param_2,undefined2 param_3,undefined1 param_4)

{
  undefined2 unaff_DS;
  
  *(undefined2 *)0x41b8 = param_1;
  *(undefined1 *)0x41c8 = param_4;
  *(undefined1 *)0x41c7 = 0;
  FUN_1000_636a(param_2,param_3);
  FUN_1000_62de();
  *(undefined1 *)0x41c6 = 0;
  return;
}


// ---- FUN_1000_63c4 @ 1000:63c4 ----

void __cdecl16near
FUN_1000_63c4(undefined2 param_1,undefined2 param_2,undefined2 param_3,undefined1 param_4)

{
  undefined2 unaff_DS;
  
  *(undefined2 *)0x41b8 = param_1;
  *(undefined1 *)0x41c8 = param_4;
  FUN_1000_636a(param_2,param_3);
  *(undefined2 *)0x41ba = 8;
  *(undefined1 *)0x41c6 = 1;
  return;
}


// ---- FUN_1000_640a @ 1000:640a ----

undefined2 __cdecl16near FUN_1000_640a(void)

{
  undefined2 uVar1;
  undefined2 unaff_DS;
  
  uVar1 = *(undefined2 *)0x41bc;
  FUN_1000_62a0();
  return uVar1;
}


// ---- FUN_1000_6413 @ 1000:6413 ----

void FUN_1000_6413(undefined1 param_1)

{
  undefined2 unaff_DS;
  
  *(undefined1 *)*(undefined2 *)0x41c2 = param_1;
  *(int *)0x41c2 = *(int *)0x41c2 + 1;
  FUN_1000_62b7();
  return;
}


// ---- FUN_1000_6425 @ 1000:6425 ----

bool __cdecl16near FUN_1000_6425(void)

{
  char *pcVar1;
  int *piVar2;
  char cVar3;
  undefined1 *puVar4;
  undefined2 unaff_DS;
  
  pcVar1 = (char *)0x41bc;
  cVar3 = *pcVar1;
  *pcVar1 = *pcVar1 << 1;
  piVar2 = (int *)0x41ba;
  *piVar2 = *piVar2 + -1;
  if (*piVar2 == 0) {
    *(undefined2 *)0x41ba = 8;
    puVar4 = (undefined1 *)*(undefined2 *)0x41c2;
    *(int *)0x41c2 = *(int *)0x41c2 + 1;
    if ((undefined1 *)*(undefined2 *)0x41c0 == puVar4) {
      FUN_1000_62ca();
    }
    else {
      *(undefined1 *)0x41bc = *puVar4;
    }
  }
  return cVar3 < '\0';
}


// ---- FUN_1000_6479 @ 1000:6479 ----

void __cdecl16near FUN_1000_6479(int param_1)

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
    pcVar1 = (char *)0x41bc;
    cVar3 = *pcVar1;
    *pcVar1 = *pcVar1 << 1;
    uVar6 = (uint)(cVar3 < '\0');
    piVar2 = (int *)0x41ba;
    *piVar2 = *piVar2 + -1;
    if (*piVar2 == 0) {
      *(undefined2 *)0x41ba = 8;
      puVar4 = (undefined1 *)*(undefined2 *)0x41c2;
      *(int *)0x41c2 = *(int *)0x41c2 + 1;
      if ((undefined1 *)*(undefined2 *)0x41c0 == puVar4) {
        FUN_1000_62ca(param_1,uVar6,uVar5);
      }
      else {
        *(undefined1 *)0x41bc = *puVar4;
      }
    }
    uVar5 = uVar5 | uVar6 << ((byte)param_1 & 0x1f);
  }
  return;
}


// ---- FUN_1000_64f0 @ 1000:64f0 ----

undefined2 __cdecl16near FUN_1000_64f0(void)

{
  undefined1 uVar1;
  undefined1 uVar2;
  
  uVar1 = FUN_1000_640a();
  uVar2 = FUN_1000_640a();
  return CONCAT11(uVar2,uVar1);
}


// ---- FUN_1000_650f @ 1000:650f ----

void __cdecl16near FUN_1000_650f(undefined1 *param_1,int param_2)

{
  uint uVar1;
  uint uVar2;
  undefined1 *puVar3;
  undefined2 uVar4;
  undefined2 unaff_DS;
  
  if (*(int *)0x41b6 == 0) {
    uVar4 = (undefined2)((ulong)param_1 >> 0x10);
    puVar3 = (undefined1 *)param_1;
    while (param_2 != 0) {
      uVar2 = param_2 - 1;
      *puVar3 = (char)*(undefined2 *)0x41bc;
      uVar1 = *(int *)0x41c0 - *(int *)0x41c2;
      if (uVar2 <= (uint)(*(int *)0x41c0 - *(int *)0x41c2)) {
        uVar1 = uVar2;
      }
      FUN_1000_6015(puVar3 + 1,uVar4,*(undefined2 *)0x41c2);
      puVar3 = puVar3 + 1 + uVar1;
      *(int *)0x41c2 = *(int *)0x41c2 + uVar1;
      FUN_1000_62a0();
      param_2 = uVar2 - uVar1;
    }
  }
  return;
}


// ---- FUN_1000_655a @ 1000:655a ----

void __cdecl16near FUN_1000_655a(undefined2 param_1,undefined2 param_2,uint param_3)

{
  uint uVar1;
  undefined2 unaff_DS;
  
  for (; param_3 != 0; param_3 = param_3 - uVar1) {
    uVar1 = *(int *)0x41c0 - *(int *)0x41c2;
    if (param_3 <= (uint)(*(int *)0x41c0 - *(int *)0x41c2)) {
      uVar1 = param_3;
    }
    FUN_1000_6015(*(undefined2 *)0x41c2);
    *(int *)0x41c2 = *(int *)0x41c2 + uVar1;
    FUN_1000_62b7();
  }
  return;
}


// ---- FUN_1000_6599 @ 1000:6599 ----

void __cdecl16near FUN_1000_6599(undefined1 *param_1,int param_2)

{
  undefined1 *puVar1;
  int iVar2;
  undefined1 *puVar3;
  undefined2 uVar4;
  
  uVar4 = (undefined2)((ulong)param_1 >> 0x10);
  puVar3 = (undefined1 *)param_1;
  for (; param_2 != 0; param_2 = param_2 + -1) {
    iVar2 = FUN_1000_640a();
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


// ---- FUN_1000_65bf @ 1000:65bf ----

void __cdecl16near FUN_1000_65bf(undefined4 param_1,int param_2)

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
  FUN_1000_655a((int)param_1,uVar3,iVar1);
  if (iVar1 != param_2) {
    FUN_1000_6413(0);
  }
  return;
}


// ---- FUN_1000_65f3 @ 1000:65f3 ----

void __cdecl16near FUN_1000_65f3(void)

{
  undefined2 unaff_DS;
  
  if (*(int *)0x41ba != 8) {
    FUN_1000_6479(*(undefined2 *)0x41ba);
  }
  return;
}


// ---- FUN_1000_6616 @ 1000:6616 ----

uint __cdecl16near FUN_1000_6616(char *param_1,int param_2,uint param_3)

{
  undefined2 unaff_DS;
  
  for (; param_2 != 0; param_2 = param_2 + -1) {
    param_3 = CONCAT11((char)(param_3 >> 8),(char)param_3 + *param_1) << 1 |
              (uint)((int)param_3 < 0);
    param_1 = param_1 + 1;
  }
  return param_3;
}


// ---- FUN_1000_6660 @ 1000:6660 ----

void __cdecl16near FUN_1000_6660(undefined1 *param_1,int param_2)

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
  uRam000166a3 = FUN_1000_640a();
                    /* WARNING: Read-only address (ram,0x000166a3) is written */
  bRam00016699 = FUN_1000_640a();
                    /* WARNING: Read-only address (ram,0x00016699) is written */
  iRam000166cb = 1 << (bRam00016699 & 0x1f);
                    /* WARNING: Read-only address (ram,0x000166cb) is written */
  uRam000166c6 = FUN_1000_640a();
                    /* WARNING: Read-only address (ram,0x000166c6) is written */
  while (puVar7 < puVar1) {
    iVar4 = FUN_1000_6425();
    if (iVar4 == 0) {
      iVar4 = FUN_1000_6479(0);
LAB_1000_669d:
      puVar6 = puVar7 + (-2 - iVar4);
      iVar4 = FUN_1000_6479(0);
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
      iVar4 = FUN_1000_6425();
      if (iVar4 == 0) {
        iVar4 = FUN_1000_6479(0);
        iVar4 = iVar4 + -0xf10;
        goto LAB_1000_669d;
      }
      uVar3 = FUN_1000_6479(8);
      puVar2 = puVar7;
      puVar7 = puVar7 + 1;
      *puVar2 = uVar3;
    }
  }
  FUN_1000_65f3();
  return;
}


