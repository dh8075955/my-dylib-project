Code Useless Aimsilent/LockCamera FreeFireMax V2.113.1 
void NoRecoil(void* instance, Vector3* recoilVec, float a1, float a2) {
    if (!Vars.SilentAim  !Vars.Enable) return;
    recoilVec->x = 0;
    recoilVec->y = 0;
    recoilVec->z = 0;
}

void bitch(void *_this, float a1, float a2) {
    if (!_this  !Vars.Enable) return;

    void* local = game_sdk->GetLocalPlayer(game_sdk->Curent_Match());
    if (!local  !game_sdk->Component_GetTransform(local)) return;

    if (!game_sdk->get_IsFiring(local)) return;

    void* target = GetClosestEnemy();
    if (!target) return;
if (game_sdk->GetHp(target) <= 0) return;
    Vector3 targetPos;

    switch (Vars.Target) {
        case HEAD:
            targetPos = GetHeadPosition(target);
            break;
        case HEADv2:
            targetPos = GetNeckPosition(target);
            break;
        case BODY:
            targetPos = GetChestPosition(target);
            break;
    }

    Vector3 eye = GetHeadPosition(local); 

    Quaternion aimRot = GetRotationToTheLocation(targetPos, 0, eye);

    if (Vars.SilentAim) {
       
        game_sdk->set_aim(local, aimRot);
    } else if (Vars.Aimbot) {
        
    }
}


void AutoHookSilentFire() {
    static bool isHooked = false;
    void* fireOffset = (void*)getRealOffset(ENCRYPTOFFSET("0x105F924D0"));
    void* noRecoilAddr = (void*)getRealOffset(ENCRYPTOFFSET("0x105EE93F0"));

    if (!Vars.SilentAim) return;

    void* match = game_sdk->Curent_Match();
    if (!match) return;

    void* local = game_sdk->GetLocalPlayer(match);
    if (!local  !game_sdk->Component_GetTransform(local)) return;

    bool isFiring = game_sdk->get_IsFiring(local);

    
    if (!isFiring && isHooked) {
        Unhook(fireOffset);
Unhook(noRecoilAddr);

        isHooked = false;
        return;
    }

  
    if (isFiring) {
        void* enemy = GetClosestEnemy();
        if (!enemy || game_sdk->GetHp(enemy) <= 0) return;

        if (!isHooked) {
            void* addr[] = { fireOffset, noRecoilAddr };
            void* func[] = { (void*)bitch, (void*)NoRecoil };
            hook(addr, func, 2);
            isHooked = true;
        }
    }
}



AutoHookSilentFire() //at get players

ImGui::Checkbox(oxorany("SilentAim"), &Vars.SilentAim);

ImGui::Checkbox(oxorany("SilentAim"), &Vars.SilentAim);
