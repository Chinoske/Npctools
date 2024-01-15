/*Made by : SymboliXDEV
Edited by : Rochet2
Edited by : Xepic90
Work% : 100% success just buffer
Buffer from level 1 to 79, level 80 will not give benefits.
Compile : Success*/

#include "Player.h"
#include "ScriptedGossip.h"
#include "Chat.h"
#include "ScriptMgr.h"

static bool BuffByLevel;
static const uint32 buffIdstools[] = { 26035, 69994, 35076, 26393, 24425, 53758, 69559, 24705, 35874, 35912, 38734, 23735, 23736, 23737,  23738, 23767, 23768, 23769, 43223, 5862, 33377, 33779, 31305, 70692, 15366, 16609, 48162, 48074, 48170, 43223, 36880, 30562, 30567, 30557, 33081, 48469 };

class tools_npc : public CreatureScript
{
public:
    tools_npc() : CreatureScript("tools_npc") { }

    bool OnGossipHello(Player* player, Creature* creature)
    {
        if (player->IsInCombat())
        {
            player->GetSession()->SendNotification("You are in Combat");
            return true;
        }

        // Placeholders for teleports
        //player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Teleport 1", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
        //player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Teleport 2", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
        AddGossipItemFor(player, GOSSIP_ICON_CHAT, "|cff00ff00|TInterface\\icons\\spell_holy_holybolt:30|t|r Dame mi UltraBuff para Levear.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);
        //player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Reset my Talents", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 4);
        //player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Remove my Sickness", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 5);
        //player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Reset my CDs", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 6);
        //AddGossipItemFor(player, GOSSIP_ICON_CHAT, "Repair Items", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 7);
        //player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Clear Combat", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 8);
        //player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Reset Instances", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 9);
        SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
        return true;
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 sender, uint32 actions)
    {
        // Who are we dealing with?
        std::string PlayerName = player->GetName();
        uint32 PlayerLevel = player->getLevel();

        // Are we buffing based on level
        if (BuffByLevel == true)

        player->PlayerTalkClass->ClearMenus();

        if (sender != GOSSIP_SENDER_MAIN || actions <= GOSSIP_ACTION_INFO_DEF)
        {
            CloseGossipMenuFor(player);
            return true;
        }

        switch (actions)
        {
         case GOSSIP_ACTION_INFO_DEF + 2:
            player->TeleportTo(1, 6457.238281f, -4244.459473f, 667.190369f, 1.446752f);
            CloseGossipMenuFor(player);
            return true;

        case GOSSIP_ACTION_INFO_DEF + 1:
            player->TeleportTo(0, 0.0f, 0.0f, 0.0f, 0.0f);
            CloseGossipMenuFor(player);
            return true;

        case GOSSIP_ACTION_INFO_DEF + 3:

            for (int i = 0; i < sizeof(buffIdstools) / sizeof(*buffIdstools); ++i)
                // Apply (10-19, 20-29, ..., 70-79, 80)
                if (PlayerLevel < 80)
                {
                    // Dish out the buffs
                    player->CastSpell(player, buffIdstools[i], true);

                } // LEVEL 80
            player->GetSession()->SendNotification("[Haz sido beneficiado por el servidor WowChile]|t|r", player->GetGUID(), true);
            player->GetSession()->SendAreaTriggerMessage("Tendras acceso a este NPC solo desde nivel 1 al 79", player->GetGUID(), true);
            player->GetSession()->SendAreaTriggerMessage("Cuando Tengas nivel maximo el boton del NPC sera bloqueado", player->GetGUID(), true);
            ClearGossipMenuFor(player);
            return true;
            break;

        case GOSSIP_ACTION_INFO_DEF + 4: // Reset Talents
            player->resetTalents(true);
            player->SendTalentsInfoData(false);
            player->GetSession()->SendAreaTriggerMessage("Your talents has been reset.", player->GetGUID(), true);
            break;

        case GOSSIP_ACTION_INFO_DEF + 5: // Remove my siccness
            if (player->HasAura(15007))
                player->RemoveAura(15007);
            break;

        case GOSSIP_ACTION_INFO_DEF + 6: // reset my CD'S
            player->SetFullHealth();
            player->SetPower(POWER_MANA, player->GetMaxPower(POWER_MANA));
            player->RemoveAllSpellCooldown();
            break;

        case GOSSIP_ACTION_INFO_DEF + 7: // repair my items
            player->DurabilityRepairAll(false, 0.0f, false);
            break;

        case GOSSIP_ACTION_INFO_DEF + 8: // Clear Combat
            player->CombatStop();
            break;

        /*case GOSSIP_ACTION_INFO_DEF + 9: // Reset all Instances For PvE 
            for (uint8 i = 0; i < MAX_DIFFICULTY; ++i)
            {
                Player::BoundInstancesMap& binds = player->GetBoundInstances(Difficulty(i));
                for (Player::BoundInstancesMap::iterator itr = binds.begin(); itr != binds.end();)
                {
                    player->UnbindInstance(itr, Difficulty(i));
                }
            }
            break;*/

        default: // Close
            CloseGossipMenuFor(player);
            return true;
        }

        OnGossipHello(player, creature);
        return true;
    }
};

void AddSC_tools_npc()
{
    new tools_npc;
}
