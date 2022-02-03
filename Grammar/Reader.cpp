#include "Reader.h"
#include "StateMachine.h"
#include "cstate_impl.h"
#include "mstate_impl.h"
struct Reader
{
    StateMachine& sm = create_statemachine();
};


Reader& create_reader()
{
    Reader* reader = new Reader;
    using namespace cstate;
    // NULLM
    insert(reader->sm, NULLM, LETTER);
    insert(reader->sm, NULLM, DIGIT2);
    insert(reader->sm, NULLM, DOT1);
    insert(reader->sm, NULLM, SIGNN);
    insert(reader->sm, NULLM, SPACEN1);
    insert(reader->sm, NULLM, QUOTE1);
    // LETTER
    insert(reader->sm, LETTER, LETTER);
    insert(reader->sm, LETTER, DIGIT1);
    insert(reader->sm, LETTER, SIGN1);
    insert(reader->sm, LETTER, SPACE1);
    // DIGIT1
    insert(reader->sm, DIGIT1, LETTER);
    insert(reader->sm, DIGIT1, DIGIT1);
    insert(reader->sm, DIGIT1, SIGN1);
    insert(reader->sm, DIGIT1, SPACE1);
    // DIGIT2
    insert(reader->sm, DIGIT2, DIGIT2);
    insert(reader->sm, DIGIT2, DOT2);
    insert(reader->sm, DIGIT2, SIGN2);
    insert(reader->sm, DIGIT2, SPACE2);
    // DIGIT3 
    insert(reader->sm, DIGIT3, DIGIT3);
    insert(reader->sm, DIGIT3, SIGN3);
    insert(reader->sm, DIGIT3, SPACE3);
    // DOT
    insert(reader->sm, DOT1, DIGIT3);
    insert(reader->sm, DOT2, DIGIT3);
    insert(reader->sm, DOT2, SIGN3);
    insert(reader->sm, DOT2, SPACE3);
    // SIGN1-2
    insert(reader->sm, SIGN1, KEYWORD);
    insert(reader->sm, SIGN2, INTEGER);
    insert(reader->sm, SIGN3, FLOAT);
    // SIGNN
    insert(reader->sm, SIGNN, LETTER);
    insert(reader->sm, SIGNN, DIGIT2);
    insert(reader->sm, SIGNN, DOT1);
    insert(reader->sm, SIGNN, SPACEN2);
    insert(reader->sm, SIGNN, SIGNN);
    insert(reader->sm, SIGNN, QUOTE1);
    // SPACE1-2
    insert(reader->sm, SPACE1, KEYWORD);
    insert(reader->sm, SPACE2, INTEGER);
    insert(reader->sm, SPACE3, FLOAT);
    // SPACEN1
    insert(reader->sm, SPACEN1, LETTER);
    insert(reader->sm, SPACEN1, DIGIT2);
    insert(reader->sm, SPACEN1, DOT1);
    insert(reader->sm, SPACEN1, SIGNN);
    insert(reader->sm, SPACEN1, SPACEN1);
    insert(reader->sm, SPACEN1, QUOTE1);
    // SPACEN2
    insert(reader->sm, SPACEN2, LETTER);
    insert(reader->sm, SPACEN2, DIGIT2);
    insert(reader->sm, SPACEN2, DOT1);
    insert(reader->sm, SPACEN2, SPACEN2);
    insert(reader->sm, SPACEN2, SIGNN);
    insert(reader->sm, SPACEN2, QUOTE1);
    // STRING
    insert(reader->sm, QUOTE1, STAR);
    insert(reader->sm, STAR, STAR);
    insert(reader->sm, STAR, QUOTE2);
    insert(reader->sm, QUOTE2, SPACE4);
    insert(reader->sm, QUOTE2, SIGN4);
    insert(reader->sm, SPACE4, STRING);
    insert(reader->sm, SIGN4, STRING);
    return *reader;
}

void delete_reader(Reader& reader)
{
    delete_statemachine(reader.sm);
}


std::ostream& operator<<(std::ostream& out, const Reader& reader)
{
    StateMachine& sm = reader.sm;
    for (size_t i = 0; i < get_size(sm); i++)
    {
        out << "digraph {" << std::endl;
        for (size_t i = 0; i < get_size(sm); i++)
            out << "\t" <<(cstate::cstate)get_begin(get_node(sm,i)) << " -> " << (cstate::cstate)get_end(get_node(sm,i)) << std::endl;
        out << "}";
        out << std::endl;
        return out;
    }
    
    return out;
}





std::vector<std::pair<std::string,cstate::cstate>> 
    parse_program( Reader& reader,  std::string program )
{
    using namespace mstate;
    using namespace cstate;
    using cstate::cstate;
    using mstate::mstate;
    std::vector<std::pair<std::string,cstate>> arr;
    cstate state = NULLM;
    std::string keyword = "";
    for (size_t i = 0; i < program.size(); i++)
    {
        char character = program[i];
        mstate type = parse_character(character);
        StateMachine& paths = get_begin(reader.sm,state);
        bool stop = false;
        for (size_t j = 0; j < get_size(paths); j++)
        {
            if(stop) break;
            cstate end = (cstate)get_end(get_node(paths,j));
            switch (end)
            {
            case DIGIT1:
            case DIGIT2:
            case DIGIT3:
                if(type == DIGITM) {
                    state = end;
                    stop = true;
                }
                break;
            case SPACE1:
            case SPACE2:
            case SPACE3:
            case SPACE4:
            case SPACEN1:
            case SPACEN2:
                if(type == SPACEM) 
                {
                    state = end;
                    stop = true;
                }
                break;
            case SIGN1:
            case SIGN2:
            case SIGN3:
            case SIGN4:
            case SIGNN:
                if(type == SIGNM) {
                    state = end;
                    stop = true;
                    arr.push_back(std::make_pair(std::string(1,character),state));
                }
                break;
            case DOT1:
            case DOT2:
                if(type == DOTM) {
                    state = end;
                    stop = true;
                }
                break;
            case LETTER:
                if(type == LETTERM) {
                    state = end;
                    stop = true;
                }
                break;
            case QUOTE1:
            case QUOTE2:
                if(type == QUOTEM) {
                    state = end;
                    stop = true;
                }
                break;
            case STAR:
                if(type != QUOTEM) {
                    state = end;
                    stop = true;
                }
                break;
            }
        }
        delete_statemachine(paths);
        
        if ( (i+1) < program.size() )
        {
            cstate next_state = state;
            char character = program[i+1];
            mstate type = parse_character(character);
            StateMachine& paths = get_begin(reader.sm,next_state);
            bool stop = false;
            for (size_t j = 0; j < get_size(paths); j++)
            {
                if(stop) break;
                cstate end = (cstate)get_end(get_node(paths,j));
                switch (end)
                {
                case DIGIT1:
                case DIGIT2:
                case DIGIT3:
                    if(type == DIGITM) {
                        next_state = end;
                        stop = true;
                    }
                    break;
                case SPACE1:
                case SPACE2:
                case SPACE3:
                case SPACE4:
                case SPACEN1:
                case SPACEN2:
                    if(type == SPACEM) 
                    {
                        next_state = end;
                        stop = true;
                    }
                    break;
                case SIGN1:
                case SIGN2:
                case SIGN3:
                case SIGN4:
                case SIGNN:
                    if(type == SIGNM) {
                        next_state = end;
                        stop = true;
                    }
                    break;
                case DOT1:
                case DOT2:
                    if(type == DOTM) {
                        next_state = end;
                        stop = true;
                    }
                    break;
                case LETTER:
                    if(type == LETTERM) {
                        next_state = end;
                        stop = true;
                    }
                    break;
                case QUOTE1:
                case QUOTE2:
                    if(type == QUOTEM) {
                        next_state = end;
                        stop = true;
                    }
                    break;
                case STAR:
                    if(type != QUOTEM) {
                        next_state = end;
                        stop = true;
                    }
                    break;
                }
                
            }
            delete_statemachine(paths);
            switch (next_state)
            {
            case SIGN1:
            case SPACE1:
                state = KEYWORD;
                break;
            case SIGN2:
            case SPACE2:
                state = INTEGER;
                break;
            case SIGN3:
            case SPACE3:
                state = FLOAT;
                break;
            case SIGN4:
            case SPACE4:
                state = STRING;
                break;
            }
        }

        if(type == LETTERM || type == DIGITM || type == DOTM || state == STAR || type == QUOTEM)
        {
            keyword+= character;
        }
        

        if (state == INTEGER || state == KEYWORD || state == FLOAT || state == STRING)
        {
            arr.push_back(std::make_pair(keyword,state));
            keyword = "";
            state = NULLM;
        }


    }
    return arr;
}


