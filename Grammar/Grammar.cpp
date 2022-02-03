#include "Grammar.h"
#include "pattern_impl.h"
#include "cstate_impl.h"
#include "util.h"
#include "scope_state_impl.h"

struct Grammar
{
    StateMachine& sm = create_statemachine();
};



Grammar& create_grammar()
{
    Grammar* temp = new Grammar;
    using namespace pattern;
    // insert(temp->sm,BEGINNING,KEYWORD1);
    insert(temp->sm,BEGINNING,KEYWORD2);
    insert(temp->sm,BEGINNING,INTEGER);
    insert(temp->sm,BEGINNING,STRING);
    insert(temp->sm,BEGINNING,SIGNPM);
    insert(temp->sm,BEGINNING,SCOPEBEGIN);
    insert(temp->sm,BEGINNING,FSCOPEEND);

    insert(temp->sm,SCOPEBEGIN,SCOPEBEGIN);
    insert(temp->sm,SCOPEBEGIN,KEYWORD1);
    insert(temp->sm,SCOPEBEGIN,INTEGER);
    insert(temp->sm,SCOPEBEGIN,SIGNPM);

    insert(temp->sm,SCOPEEND,END);
    insert(temp->sm,SCOPEEND,SIGN);
    insert(temp->sm,SCOPEEND,CALL2);
    insert(temp->sm,SCOPEEND,COMMAC);

    insert(temp->sm,SIGNPM,KEYWORD1);
    insert(temp->sm,SIGNPM,INTEGER);
    insert(temp->sm,SIGNPM,SCOPEBEGIN);

    insert(temp->sm,SIGN,KEYWORD1);
    insert(temp->sm,SIGN,INTEGER);
    insert(temp->sm,SIGN,SIGNPM);

    insert(temp->sm,SIGNE,FSCOPEBEGIN);
    insert(temp->sm,SIGNE,SCOPEBEGIN);
    insert(temp->sm,SIGNE,KEYWORD2);
    insert(temp->sm,SIGNE,STRING);
    insert(temp->sm,SIGNE,INTEGER);
    insert(temp->sm,SIGNE,SIGNPM);

    insert(temp->sm,FSCOPEBEGIN,ARGBEGIN);

    insert(temp->sm,FSCOPEEND,STRING);
    insert(temp->sm,FSCOPEEND,INTEGER);
    insert(temp->sm,FSCOPEEND,KEYWORD5);
    insert(temp->sm,FSCOPEEND,SCOPEBEGIN);
    insert(temp->sm,FSCOPEEND,END);
    insert(temp->sm,FSCOPEEND,SIGNPM);

    insert(temp->sm,STRING,END);
    insert(temp->sm,STRING,SIGNP2);
    insert(temp->sm,STRING,CALL2);
    insert(temp->sm,STRING,COMMAC);

    insert(temp->sm,KEYWORD1,END);
    insert(temp->sm,KEYWORD1,SIGN);
    insert(temp->sm,KEYWORD1,SCOPEEND);
    insert(temp->sm,KEYWORD1,CALL1);

    insert(temp->sm,KEYWORD2,END);
    insert(temp->sm,KEYWORD2,SIGNE);
    insert(temp->sm,KEYWORD2,SIGNP1);
    insert(temp->sm,KEYWORD2,SIGN);
    insert(temp->sm,KEYWORD2,CALL1);

    insert(temp->sm,KEYWORD3,END);
    insert(temp->sm,KEYWORD3,SIGNP2);
    insert(temp->sm,KEYWORD3,CALL2);
    insert(temp->sm,KEYWORD3,CALL1);
    insert(temp->sm,KEYWORD3,COMMAC);
    
    insert(temp->sm,KEYWORD4,COMMA);
    insert(temp->sm,KEYWORD4,ARGEND);

    insert(temp->sm,KEYWORD5,END);
    insert(temp->sm,KEYWORD5,SIGNP3);
    insert(temp->sm,KEYWORD5,SIGN);
    insert(temp->sm,KEYWORD5,CALL1);
    insert(temp->sm,KEYWORD5,CALL2);

    insert(temp->sm,ARGBEGIN,ARGEND);
    insert(temp->sm,ARGBEGIN,KEYWORD4);

    insert(temp->sm,ARGEND,KEYWORD1);
    insert(temp->sm,ARGEND,STRING);
    insert(temp->sm,ARGEND,INTEGER);
    insert(temp->sm,ARGEND,FSCOPEEND);

    insert(temp->sm,COMMA,KEYWORD4);

    insert(temp->sm,INTEGER,END);
    insert(temp->sm,INTEGER,SIGN);
    insert(temp->sm,INTEGER,SCOPEEND);
    insert(temp->sm,INTEGER,CALL2);
    insert(temp->sm,INTEGER,COMMAC);

    insert(temp->sm,SIGNP1,STRING);
    insert(temp->sm,SIGNP1,INTEGER);
    insert(temp->sm,SIGNP1,KEYWORD5);
    insert(temp->sm,SIGNP1,SCOPEBEGIN);
    insert(temp->sm,SIGNP1,SIGNPM);
    
    insert(temp->sm,SIGNP2,STRING);
    insert(temp->sm,SIGNP2,KEYWORD3);

    insert(temp->sm,SIGNP3,STRING);
    insert(temp->sm,SIGNP3,INTEGER);
    insert(temp->sm,SIGNP3,SCOPEBEGIN);
    insert(temp->sm,SIGNP3,KEYWORD5);
    insert(temp->sm,SIGNP3,SIGNPM);

    insert(temp->sm,CALL1,CALL2);
    insert(temp->sm,CALL1,STRING);
    insert(temp->sm,CALL1,INTEGER);
    insert(temp->sm,CALL1,SCOPEBEGIN);
    insert(temp->sm,CALL1,SIGNPM);
    insert(temp->sm,CALL1,KEYWORD5);

    insert(temp->sm,COMMAC,STRING);
    insert(temp->sm,COMMAC,INTEGER);
    insert(temp->sm,COMMAC,SCOPEBEGIN);
    insert(temp->sm,COMMAC,SIGNPM);
    insert(temp->sm,COMMAC,KEYWORD5);

    insert(temp->sm,CALL2,END);
    insert(temp->sm,CALL2,SIGNP3);
    insert(temp->sm,CALL2,SIGN);
    insert(temp->sm,CALL2,CALL2);
    insert(temp->sm,CALL2,SCOPEEND);

    return *temp;
}

void delete_grammar(Grammar& grammar)
{
    delete_statemachine(grammar.sm);
}

std::ostream& operator<<(std::ostream& out, const Grammar& grammar)
{
    StateMachine& sm = grammar.sm;

    out << "digraph {" << std::endl;
    out << "\tnode [style=filled]" << std::endl;
    pattern::print_styles();
    for (size_t i = 0; i < get_size(sm); i++)
    {
        out << "\t";
        out << (pattern::pattern)get_begin(get_node(sm,i));
        out << " -> ";
        out << (pattern::pattern)get_end(get_node(sm,i));
        out << std::endl;
    }
    out << "}";
    out << std::endl;
    return out;
}

bool is_valid_pattern(
    const Grammar& grammar
    , const std::vector<std::pair<std::string,cstate::cstate>>& feed
)
{
    using pattern::pattern;
    using cstate::cstate;
    using scope_state::scope_state;
    pattern state = pattern::BEGINNING;
    scope_state current_scope_state = scope_state::UNSPECIFIED;
    std::vector<unsigned> scopebegin, scopeend;
    int scope = 0, fscope = 0;
    std::vector<pattern> prescope;

    for (size_t i = 0; i < feed.size(); i++)
    {
        const auto& feedi = feed[i];
        if(state == pattern::END) {
            if (scope != 0)
                return false;
            
            scope = 0;
            state = pattern::BEGINNING;
            // TODO: check if there's a mismatch
            // }}{{ --incorrect 0 -1 -2 -1 0
            // {}}{ --incorrect 0 1 0 -1 0
            // {}{} --correct 0 1 0 1 0 
            // {{}} -- correct 0 1 2 1 0
            // }}}{{{ -- incorrect 0 -1 -2 -3 -2 -1 0
            // {}}}{{ -- incorrect 0 1 0 -1 -2 -1 0
            // {}{}}{ -- incorrect 0 1 0 1 0 -1 0
            // {}{}{} -- correct 0 1 0 1 0 1 0
            
            if(scopebegin.size() != scopeend.size())
                return false;
            
            scopebegin.clear();
            scopeend.clear();
            prescope.clear();
        }
        bool stop = false;
        if(state == pattern::CALL1 || state == pattern::SCOPEBEGIN)
            scope++;
        else if (state == pattern::CALL2 || state == pattern::SCOPEEND)
            scope--;
        
        if(scope < 0) return false;

        StateMachine& paths = get_begin(grammar.sm, state);
        

        for (size_t j = 0; j < get_size(paths); j++)
        {
            if(stop == true) break;
            int k = 0;
            pattern end = (pattern)get_end(get_node(paths,j));

            if (feedi.first == "return")
            {
                k= 1;
            }
            
            switch(feedi.second) 
            {
            case cstate::KEYWORD:
            {
                bool keyword = feedi.first == "take" || feedi.first == "return";
                if(
                    keyword
                    && (
                       end == pattern::FSCOPEBEGIN
                    || end == pattern::FSCOPEEND
                    )
                )
                {
                    if( end == pattern::FSCOPEBEGIN)
                        fscope++;
                    else if (end == pattern::FSCOPEEND)
                    {
                        fscope--;
                        if(fscope < 0) return 0;
                    }
                    state = end;
                    stop = true;
                } else if ( keyword == false)
                {
                    switch (end)
                    {
                    case pattern::KEYWORD1:
                    case pattern::KEYWORD2:
                    case pattern::KEYWORD3:
                    case pattern::KEYWORD4:
                    case pattern::KEYWORD5:
                    {
                        state = end;
                        stop = true;
                        break;
                    }
                    }
                }
                break;
            }
            case cstate::FLOAT:
            case cstate::INTEGER:
            {

                if(end == pattern::INTEGER)
                {
                    if(current_scope_state == scope_state::STRING)
                        return false;
                    state = end;
                    stop = true;
                }
                break;
            }
            case cstate::STRING:
            {

                if(end == pattern::STRING)
                {
                    if(current_scope_state == scope_state::INTEGER)
                        return false;
                    state = end;
                    stop = true;
                }
                break;
            }
            case cstate::SIGN1:
            case cstate::SIGN2:
            case cstate::SIGN3:
            case cstate::SIGNN:
            {
                // TODO: implement END SIGNP1-2 SIGNPM SIGNE ARGBEGIN ARGEND
                switch (end)
                {
                case pattern::END:
                {
                    if(feedi.first == ";")
                    {
                        state = end;
                        stop = true;
                    }
                    break;
                }
                case pattern::SIGNE:
                {
                    if(feedi.first == "=")
                    {
                        state = end;
                        stop = true;
                    }
                    break;
                }
                case pattern::SIGN:
                {
                    if(is_sign(feedi.first))
                    {
                        state = end;
                        stop = true;
                    }
                    break;
                }
                case pattern::SIGNP1:
                case pattern::SIGNP2:
                case pattern::SIGNP3:
                {
                    if(feedi.first == "+")
                    {
                        state = end;
                        stop = true;
                    }
                    break;
                }
                case pattern::SIGNPM:
                {
                    if(feedi.first == "+" || feedi.first == "-")
                    {
                        state = end;
                        stop = true;
                    }
                    break;
                }
                case pattern::ARGBEGIN:
                case pattern::CALL1:
                {
                    if(feedi.first == "(" )
                    {
                        if(end == pattern::CALL1) 
                            prescope.push_back(state);
                        state = end;
                        stop = true;
                    }
                    break;
                }
                case pattern::ARGEND:
                case pattern::CALL2:
                {
                    if(feedi.first == ")" )
                    {
                        if(end == pattern::CALL2)
                        {
                            pattern last =prescope.back();
                            prescope.pop_back();
                            switch (last)
                            {
                            case pattern::KEYWORD2:
                            case pattern::KEYWORD5:
                                current_scope_state = scope_state::UNSPECIFIED;
                                break;
                            case pattern::KEYWORD3:
                                current_scope_state = scope_state::STRING;
                                break;
                            case pattern::KEYWORD1:
                                current_scope_state = scope_state::INTEGER;
                                break;
                            
                            }
                        }
                        state = end;
                        stop = true;
                    }
                    break;
                }

                case pattern::SCOPEBEGIN:
                {
                    if(feedi.first == "{" )
                    {
                        scopebegin.push_back(i);
                        state = end;
                        stop = true;
                    }
                    break;
                }
                case pattern::SCOPEEND:
                {
                    if(feedi.first == "}" )
                    {
                        scopeend.push_back(i);
                        state = end;
                        stop = true;
                    }
                    break;
                }
                case pattern::COMMA:
                case pattern::COMMAC:
                {
                    if(feedi.first == "," )
                    {
                        state = end;
                        stop = true;
                    }
                    break;
                }
                }
                break;
            }
            }
        }
        delete_statemachine(paths);
        if(stop == false)
        {
            return false;
        }
    }
    if(fscope !=0)
        return false;
    
    if(state == pattern::END)
    {
        return true;
    } else 
    {
        return false;
    }
}