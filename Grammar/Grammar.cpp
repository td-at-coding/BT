#include "Grammar.h"
#include "pattern_impl.h"
#include "cstate_impl.h"
#include "util.h"
#include "scope_state_impl.h"
#include "Term.h"
#include "Tree.h"
struct Grammar
{
    StateMachine& sm = create_statemachine();
};



Grammar& create_grammar()
{
    Grammar* temp = new Grammar;
    // using namespace pattern;
    // insert(temp->sm,BEGINNING,KEYWORD1);
    insert(temp->sm,pattern::BEGINNING,pattern::KEYWORD2);
    insert(temp->sm,pattern::BEGINNING,pattern::INTEGER);
    insert(temp->sm,pattern::BEGINNING,pattern::STRING);
    insert(temp->sm,pattern::BEGINNING,pattern::SIGNPM);
    insert(temp->sm,pattern::BEGINNING,pattern::SCOPEBEGIN);
    insert(temp->sm,pattern::BEGINNING,pattern::FSCOPEEND);

    insert(temp->sm,pattern::SCOPEBEGIN,pattern::SCOPEBEGIN);
    insert(temp->sm,pattern::SCOPEBEGIN,pattern::KEYWORD1);
    insert(temp->sm,pattern::SCOPEBEGIN,pattern::INTEGER);
    insert(temp->sm,pattern::SCOPEBEGIN,pattern::SIGNPM);

    insert(temp->sm,pattern::SCOPEEND,pattern::END);
    insert(temp->sm,pattern::SCOPEEND,pattern::SIGN);
    insert(temp->sm,pattern::SCOPEEND,pattern::CALL2);
    insert(temp->sm,pattern::SCOPEEND,pattern::COMMAC);

    insert(temp->sm,pattern::SIGNPM,pattern::KEYWORD1);
    insert(temp->sm,pattern::SIGNPM,pattern::INTEGER);
    insert(temp->sm,pattern::SIGNPM,pattern::SCOPEBEGIN);

    insert(temp->sm,pattern::SIGN,pattern::KEYWORD1);
    insert(temp->sm,pattern::SIGN,pattern::INTEGER);
    insert(temp->sm,pattern::SIGN,pattern::SIGNPM);

    insert(temp->sm,pattern::SIGNE,pattern::FSCOPEBEGIN);
    insert(temp->sm,pattern::SIGNE,pattern::SCOPEBEGIN);
    insert(temp->sm,pattern::SIGNE,pattern::KEYWORD2);
    insert(temp->sm,pattern::SIGNE,pattern::STRING);
    insert(temp->sm,pattern::SIGNE,pattern::INTEGER);
    insert(temp->sm,pattern::SIGNE,pattern::SIGNPM);

    insert(temp->sm,pattern::FSCOPEBEGIN,pattern::ARGBEGIN);

    insert(temp->sm,pattern::FSCOPEEND,pattern::STRING);
    insert(temp->sm,pattern::FSCOPEEND,pattern::INTEGER);
    insert(temp->sm,pattern::FSCOPEEND,pattern::KEYWORD5);
    insert(temp->sm,pattern::FSCOPEEND,pattern::SCOPEBEGIN);
    insert(temp->sm,pattern::FSCOPEEND,pattern::END);
    insert(temp->sm,pattern::FSCOPEEND,pattern::SIGNPM);

    insert(temp->sm,pattern::STRING,pattern::END);
    insert(temp->sm,pattern::STRING,pattern::SIGNP2);
    insert(temp->sm,pattern::STRING,pattern::CALL2);
    insert(temp->sm,pattern::STRING,pattern::COMMAC);

    insert(temp->sm,pattern::KEYWORD1,pattern::END);
    insert(temp->sm,pattern::KEYWORD1,pattern::SIGN);
    insert(temp->sm,pattern::KEYWORD1,pattern::SCOPEEND);
    insert(temp->sm,pattern::KEYWORD1,pattern::CALL1);

    insert(temp->sm,pattern::KEYWORD2,pattern::END);
    insert(temp->sm,pattern::KEYWORD2,pattern::SIGNE);
    insert(temp->sm,pattern::KEYWORD2,pattern::SIGNP1);
    insert(temp->sm,pattern::KEYWORD2,pattern::SIGN);
    insert(temp->sm,pattern::KEYWORD2,pattern::CALL1);

    insert(temp->sm,pattern::KEYWORD3,pattern::END);
    insert(temp->sm,pattern::KEYWORD3,pattern::SIGNP2);
    insert(temp->sm,pattern::KEYWORD3,pattern::CALL2);
    insert(temp->sm,pattern::KEYWORD3,pattern::CALL1);
    insert(temp->sm,pattern::KEYWORD3,pattern::COMMAC);
    
    insert(temp->sm,pattern::KEYWORD4,pattern::COMMA);
    insert(temp->sm,pattern::KEYWORD4,pattern::ARGEND);

    insert(temp->sm,pattern::KEYWORD5,pattern::END);
    insert(temp->sm,pattern::KEYWORD5,pattern::SIGNP3);
    insert(temp->sm,pattern::KEYWORD5,pattern::SIGN);
    insert(temp->sm,pattern::KEYWORD5,pattern::CALL1);
    insert(temp->sm,pattern::KEYWORD5,pattern::CALL2);

    insert(temp->sm,pattern::ARGBEGIN,pattern::ARGEND);
    insert(temp->sm,pattern::ARGBEGIN,pattern::KEYWORD4);

    insert(temp->sm,pattern::ARGEND,pattern::KEYWORD1);
    insert(temp->sm,pattern::ARGEND,pattern::STRING);
    insert(temp->sm,pattern::ARGEND,pattern::INTEGER);
    insert(temp->sm,pattern::ARGEND,pattern::FSCOPEEND);

    insert(temp->sm,pattern::COMMA,pattern::KEYWORD4);

    insert(temp->sm,pattern::INTEGER,pattern::END);
    insert(temp->sm,pattern::INTEGER,pattern::SIGN);
    insert(temp->sm,pattern::INTEGER,pattern::SCOPEEND);
    insert(temp->sm,pattern::INTEGER,pattern::CALL2);
    insert(temp->sm,pattern::INTEGER,pattern::COMMAC);

    insert(temp->sm,pattern::SIGNP1,pattern::STRING);
    insert(temp->sm,pattern::SIGNP1,pattern::INTEGER);
    insert(temp->sm,pattern::SIGNP1,pattern::KEYWORD5);
    insert(temp->sm,pattern::SIGNP1,pattern::SCOPEBEGIN);
    insert(temp->sm,pattern::SIGNP1,pattern::SIGNPM);
    
    insert(temp->sm,pattern::SIGNP2,pattern::STRING);
    insert(temp->sm,pattern::SIGNP2,pattern::KEYWORD3);

    insert(temp->sm,pattern::SIGNP3,pattern::STRING);
    insert(temp->sm,pattern::SIGNP3,pattern::INTEGER);
    insert(temp->sm,pattern::SIGNP3,pattern::SCOPEBEGIN);
    insert(temp->sm,pattern::SIGNP3,pattern::KEYWORD5);
    insert(temp->sm,pattern::SIGNP3,pattern::SIGNPM);

    insert(temp->sm,pattern::CALL1,pattern::CALL2);
    insert(temp->sm,pattern::CALL1,pattern::STRING);
    insert(temp->sm,pattern::CALL1,pattern::INTEGER);
    insert(temp->sm,pattern::CALL1,pattern::SCOPEBEGIN);
    insert(temp->sm,pattern::CALL1,pattern::SIGNPM);
    insert(temp->sm,pattern::CALL1,pattern::KEYWORD5);

    insert(temp->sm,pattern::COMMAC,pattern::STRING);
    insert(temp->sm,pattern::COMMAC,pattern::INTEGER);
    insert(temp->sm,pattern::COMMAC,pattern::SCOPEBEGIN);
    insert(temp->sm,pattern::COMMAC,pattern::SIGNPM);
    insert(temp->sm,pattern::COMMAC,pattern::KEYWORD5);

    insert(temp->sm,pattern::CALL2,pattern::END);
    insert(temp->sm,pattern::CALL2,pattern::SIGNP3);
    insert(temp->sm,pattern::CALL2,pattern::SIGN);
    insert(temp->sm,pattern::CALL2,pattern::CALL2);
    insert(temp->sm,pattern::CALL2,pattern::SCOPEEND);

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
    , const std::vector<
        std::pair<std::string
        , cstate::cstate>>& feed
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


#include "var_type.h"


bool is_valid_program(
    const Grammar& grammar
    , const std::vector
    <
        std::pair
        <
            std::string
            , cstate::cstate
        >
    >& feed
    , State& s
    , std::vector<Term>& terms
)
{
    using pattern::pattern;
    using cstate::cstate;
    using scope_state::scope_state;
    // using var_type::var_type;
    pattern state = pattern::BEGINNING;
    scope_state current_scope_state = scope_state::UNSPECIFIED;
    std::vector<unsigned> scopebegin, scopeend;
    int scope = 0, fscope = 0;
    std::vector<pattern> prescope;
    State _s = s;
    Term value;
    bool assignment = false;
    std::string prev_keyword = "";
    std::vector<Leaf*> leaves;
    bool muldiv = false;
    bool name_contained = false;

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
                        // assignment has been set yet
                        // only first time
                        if(assignment == false)
                        {
                            prev_keyword = feedi.first;
                            name_contained = s.contains_name(feedi.first);
                        }
                        if(s.contains_name(feedi.first))
                        {
                            var_type t;
                            s.get_type(feedi.first, t);
                            Leaf& leaf = create_leaf();
                            switch (t)
                            {
                            case INTEGER:
                            {
                                int tmp;
                                s.get_value(feedi.first, tmp);
                                set(leaf, std::to_string(tmp), cstate::INTEGER, scope);
                                leaves.push_back(&leaf);
                                break;
                            }
                            
                            case FLOAT:
                            {
                                float tmp;
                                s.get_value(feedi.first, tmp);
                                set(leaf, std::to_string(tmp), cstate::FLOAT, scope);
                                leaves.push_back(&leaf);
                                break;
                            }
                            case STRING:
                            {
                                std::string tmp;
                                s.get_value(feedi.first, tmp);
                                set(leaf, tmp, cstate::STRING, scope);
                                leaves.push_back(&leaf);
                                break;
                            }
                            default:
                                break;
                            }
                        }

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
                    Leaf& leaf = create_leaf();
                    set(leaf, feedi.first,feedi.second, scope);
                    leaves.push_back(&leaf);
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
                    Leaf& leaf = create_leaf();
                    set(leaf, feedi.first,feedi.second, scope);
                    leaves.push_back(&leaf);
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
                switch (end)
                {
                case pattern::END:
                {
                    if(feedi.first == ";")
                    {
                        state = end;
                        if (assignment == true && name_contained == true)
                        {
                            leaves.erase(leaves.begin() );

                        }
                        
                        if(muldiv == true)
                        {
                            inc(*leaves.back());
                            muldiv = false;
                        }
                        int highest = 0;
                        for (size_t i = 0; i < leaves.size(); i++)
                        {
                            Leaf& leaf = *leaves[i];
                            auto cscope = get_scope(leaf);
                            if(cscope > highest)
                                highest = cscope;
                        }
                        
                        for (int i = highest; i >= 1; i--)
                        {
                            std::vector<Leaf*> new_leaves;
                            for (size_t j = 0; j < leaves.size(); j++)
                            {
                                Leaf& leaf = *leaves[j];
                                if(get_scope(leaf) == i)
                                    new_leaves.push_back(&leaf);
                            }
                            Leaf& result_leaf = *new_leaves[0];

                            char sign = '+';
                            bool sign_changed = false, negate_value = false, negate_once = false;
                            switch (get_type(result_leaf))
                            {
                            case cstate::SIGN1:
                            case cstate::SIGN2:
                            case cstate::SIGN3:
                            case cstate::SIGNN:
                            {
                                if(get_value(result_leaf)[0] == '-')
                                    negate_once = true;
                            }
                            }
                            for (size_t j = 1; j < new_leaves.size(); j++)
                            {
                                Leaf& leaf = *new_leaves[j];
                                switch (get_type(leaf))
                                {
                                case cstate::SIGN1:
                                case cstate::SIGN2:
                                case cstate::SIGN3:
                                case cstate::SIGNN:
                                {
                                    if(sign_changed == true )
                                    {
                                        if(get_value(leaf)[0] == '-')
                                            negate_value = true;
                                        sign_changed = false;
                                    } else
                                    {
                                        sign = get_value(leaf)[0];
                                        sign_changed = true;
                                    }
                                    break;
                                }
                                
                                default:
                                {
                                    if(negate_value == true)
                                    {
                                        negate(leaf);
                                        negate_value = false;
                                    }
                                    if (negate_once == true)
                                    {
                                        negate(leaf);
                                        move(result_leaf, leaf);
                                        negate_once = false;
                                    }
                                    else
                                    {
                                        switch (sign)
                                        {
                                        case '+':
                                            add(result_leaf,leaf);
                                            break;
                                        case '-':
                                            sub(result_leaf,leaf);
                                            break;
                                        case '*':
                                            mul(result_leaf,leaf);
                                            break;
                                        case '/':
                                            div(result_leaf,leaf);
                                            break;
                                        
                                        default:
                                            break;
                                        }

                                    }
                                    break;
                                }
                                }
                            }
                            dec(result_leaf);
                        }
                        std::vector<Leaf*> new_leaves;
                        for (size_t i = 0; i < leaves.size(); i++)
                        {
                            Leaf& leaf = *leaves[i];
                            if(get_scope(leaf) == 0)
                                new_leaves.push_back(&leaf);
                        }
                        Leaf& result_leaf = *new_leaves[0];
                        char sign = '+';
                        bool sign_changed = false, negate_value = false, negate_once = false;
                        switch (get_type(result_leaf))
                        {
                        case cstate::SIGN1:
                        case cstate::SIGN2:
                        case cstate::SIGN3:
                        case cstate::SIGNN:
                        {
                            if(get_value(result_leaf)[0] == '-')
                                negate_once = true;
                        }
                        }
                        for (size_t i = 1; i < new_leaves.size(); i++)
                        {
                            Leaf& leaf = *new_leaves[i];
                            switch (get_type(leaf))
                            {
                            case cstate::SIGN1:
                            case cstate::SIGN2:
                            case cstate::SIGN3:
                            case cstate::SIGNN:
                            {
                                if(sign_changed == true )
                                {
                                    if(get_value(leaf)[0] == '-')
                                        negate_value = true;
                                    sign_changed = false;
                                } else
                                {
                                    sign = get_value(leaf)[0];
                                    sign_changed = true;
                                }
                                break;
                            }
                            
                            default:
                            {
                                if(negate_value == true)
                                {
                                    negate(leaf);
                                    negate_value = false;
                                } 
                                if (negate_once == true)
                                {
                                    negate(leaf);
                                    move(result_leaf, leaf);
                                    negate_once = false;
                                }
                                else
                                {
                                    switch (sign)
                                    {
                                    case '+':
                                        add(result_leaf,leaf);
                                        break;
                                    case '-':
                                        sub(result_leaf,leaf);
                                        break;
                                    case '*':
                                        mul(result_leaf,leaf);
                                        break;
                                    case '/':
                                        div(result_leaf,leaf);
                                        break;
                                    
                                    default:
                                        break;
                                    }

                                }
                                
                                break;
                            }
                            }
                        }
                        std::string result = get_value(result_leaf);
                        if( assignment == true)
                        {
                            var_type t;
                            cstate type_leaf = get_type(result_leaf);
                            switch (type_leaf)
                            {
                            case cstate::INTEGER:
                                t = INTEGER;
                                break;
                            case cstate::FLOAT:
                                t = FLOAT;
                                break;
                            case cstate::STRING:
                                t = STRING;
                                break;
                            
                            default:
                                break;
                            }
                            if (name_contained)
                                s.set_value(prev_keyword,result, t);
                            else
                                s.insert_data(prev_keyword,result, t);
                            name_contained = false;
                            assignment = false;
                        }
                        value.init(get_value(result_leaf),0);
                        for (size_t i = 0; i < leaves.size(); i++)
                            delete_leaf(*leaves[i]);
                        leaves.clear();
                        terms.push_back(value);
                        value.init(0,0);
                        assignment = false;
                        stop = true;
                    }
                    break;
                }
                case pattern::SIGNE:
                {
                    if(feedi.first == "=")
                    {
                        state = end;
                        assignment = true;
                        stop = true;
                    }
                    break;
                }
                case pattern::SIGN:
                {
                    if(is_sign(feedi.first))
                    {
                        Leaf& leaf = create_leaf();
                        set(leaf, feedi.first,feedi.second, scope);
                        switch (feedi.first[0])
                        {
                        case '*':
                        case '/':
                        {
                            if(muldiv == false)
                                inc(leaf);
                            inc(*leaves.back());
                            muldiv = true;
                            break;
                        }
                        case '+':
                        case '-':
                        {
                            if(muldiv == true)
                            {
                                inc(*leaves.back());
                                muldiv = false;
                            }
                            break;
                        }
                        default:
                            break;
                        }
                        leaves.push_back(&leaf);
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
                        Leaf& leaf = create_leaf();
                        set(leaf, feedi.first,feedi.second, scope);
                        leaves.push_back(&leaf);
                        state = end;
                        stop = true;
                    }
                    break;
                }
                case pattern::SIGNPM:
                {
                    if(feedi.first == "+" || feedi.first == "-")
                    {
                        Leaf& leaf = create_leaf();
                        set(leaf, feedi.first,feedi.second, scope);
                        leaves.push_back(&leaf);
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
        s = _s;
        return false;
    }
}