////////////////////////////////////////////////////////////////////////
//																	  //
//																	  //
//																	  //
//              													  //
//            														  //
//				 test           								      //
//																	  //
//                                                                    //
////////////////////////////////////////////////////////////////////////

class magdas_npc : public CreatureScript
{
    enum
    {
        GOSSIP_BUFFS,
    };

public:
    magdas_npc() : CreatureScript("magdas_npc"){}

    bool OnGossipHello(Player * pPlayer, Creature * pCreature)
    {
        pPlayer->PlayerTalkClass->ClearMenus();
		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Buff me!", GOSSIP_SENDER_MAIN, GOSSIP_BUFFS);
		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Cerrar Ventana", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 25);
        pPlayer->PlayerTalkClass->SendGossipMenu(907, pCreature->GetGUID());
	
		return true;
    }
	
    bool OnGossipSelect(Player * pPlayer, Creature * pCreature, uint32 sender, uint32 uiAction)
    {
        pPlayer->PlayerTalkClass->ClearMenus();
		// Dont let players use teleporter in combat
        if (pPlayer->IsInCombat())
        {
            pPlayer->Whisper("You should be out of combat!", LANG_UNIVERSAL, pPlayer);
            pPlayer->CLOSE_GOSSIP_MENU();
            return false;
        }

        switch (uiAction)
        {
        case GOSSIP_BUFFS: // Buff
            pPlayer->CastSpell(pPlayer, 48102, true); // Stamina
            pPlayer->CastSpell(pPlayer, 48073, true); // Divine Spirit
            pPlayer->CastSpell(pPlayer, 48169, true); // Shadow Protection
            pPlayer->CastSpell(pPlayer, 48161, true); // PW:F
            pPlayer->CastSpell(pPlayer, 43223, true); // Blessing of Kings
            pPlayer->CastSpell(pPlayer, 42995, true); // Arcane Intellect
            pPlayer->CastSpell(pPlayer, 48469, true); // Mark of the Wild
            pPlayer->CLOSE_GOSSIP_MENU();
            break;
        case GOSSIP_ACTION_INFO_DEF + 25:
            pPlayer->CLOSE_GOSSIP_MENU();
            break;
        }
        return true;
    }
};

// quest test
#define QUEST_ID 11876
class instant_80 : public CreatureScript
{
public:
   instant_80() : CreatureScript("instant_80") {}

 bool OnQuestComplete(Player * pPlayer, Creature * pCreature, Quest const * quest)
{
if(quest->GetQuestId() == QUEST_ID)
  pPlayer->SetLevel(80);
return true;
}

};

class npc_dos : public CreatureScript
{
    public:
        npc_dos() : CreatureScript("npc_dos") { }

        bool OnQuestAccept(Player* player, Creature* creature, Quest const* quest) override
        {
            if (quest->GetQuestId() == 180000)
                player->SetLevel(80);

            return true;
        }
};

void AddSC_magda_npc()
{
    new magdas_npc();
	new instant_80();
	new npc_dos();
}