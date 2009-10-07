#ifndef _H_SM_DIALOG_INFO_SM
#define _H_SM_DIALOG_INFO_SM

/*
 * ex: set ro:
 * DO NOT EDIT.
 * generated by smc (http://smc.sourceforge.net/)
 * from file : sm_dialog_info.sm
 */


#define SMC_USES_IOSTREAMS

#define SMC_NO_EXCEPTIONS

#include <statemap.h>

namespace dgo
{
    // Forward declarations.
    class map_dialog_info;
    class map_dialog_info_Initialized;
    class map_dialog_info_Default;
    class sip_dialog_infoState;
    class sip_dialog_infoContext;
    class sip_dialog_info;

    class sip_dialog_infoState :
        public statemap::State
    {
    public:

        sip_dialog_infoState(const char *name, int stateId)
        : statemap::State(name, stateId)
        {};

        virtual void Entry(sip_dialog_infoContext&) {};
        virtual void Exit(sip_dialog_infoContext&) {};


    protected:

        virtual void Default(sip_dialog_infoContext& context);
    };

    class map_dialog_info
    {
    public:

        static map_dialog_info_Initialized Initialized;
    };

    class map_dialog_info_Default :
        public sip_dialog_infoState
    {
    public:

        map_dialog_info_Default(const char *name, int stateId)
        : sip_dialog_infoState(name, stateId)
        {};

    };

    class map_dialog_info_Initialized :
        public map_dialog_info_Default
    {
    public:
        map_dialog_info_Initialized(const char *name, int stateId)
        : map_dialog_info_Default(name, stateId)
        {};

    };

    class sip_dialog_infoContext :
        public statemap::FSMContext
    {
    public:

        sip_dialog_infoContext(sip_dialog_info& owner)
        : FSMContext(map_dialog_info::Initialized),
          _owner(owner)
        {};

        sip_dialog_infoContext(sip_dialog_info& owner, const statemap::State& state)
        : FSMContext(state),
          _owner(owner)
        {};

        virtual void enterStartState()
        {
            getState().Entry(*this);
            return;
        }

        sip_dialog_info& getOwner() const
        {
            return (_owner);
        };

        sip_dialog_infoState& getState() const
        {
            if (_state == NULL)
            {
                assert(1 == 0);
            }

            return (dynamic_cast<sip_dialog_infoState&>(*_state));
        };

    private:

        sip_dialog_info& _owner;
    };
}


/*
 * Local variables:
 *  buffer-read-only: t
 * End:
 */

#endif // _H_SM_DIALOG_INFO_SM
