#include "word_expansion.h"

/*
 * perform tilde expansion.
 *
 * returns the malloc'd expansion of the tilde prefix, NULL if expansion failed.
 */
char* expand_tilde(char* string) {
    char *home = NULL;
    size_t len = strlen(s);
    char   *s2 = NULL;
    struct symtab_entry_s *entry;

    /* null tilde prefix. substitute with the value of home */
    if (len == 1) {
        entry = get_symtab_entry("HOME");
        if (entry && entry->val) {
            home = entry->val;
        } else {
            /*
             * POSIX doesn't say what to do if $HOME is null/unset.. we follow
             * what bash does, which is searching our home directory in the password
             * database.
             */
            struct passwd *pass;
            pass = getpwuid(getuid());
            if (pass) {
                /* get the value of home */
                home = pass->pw_dir;
            }
        }
    } else {
        /* we have a login name */
        struct passwd *pass;
        pass = getpwnam(s+1);
        if (pass) {
            home = pass->pw_dir;
        }
    }

    /* we have a NULL value */
    if (!home) {
        return NULL;
    }

    /* return the home dir we've found */
    s2 = malloc(strlen(home)+1);
    if (!s2) {
        return NULL;
    }
    strcpy(s2, home);
    return s2;
}

/*
 * find the closing quote that matches the opening quote, which is the first
 * char of the data string.
 * sq_nesting is a flag telling us if we should allow single quote nesting
 * (prohibited by POSIX, but allowed in ANSI-C strings).
 *
 * returns the zero-based index of the closing quote.. a return value of 0
 * means we didn't find the closing quote.
 */
size_t find_closing_quote(char* data) {
    // check the type of quote we have
    char quote = data[0];
    if (quote != '\'' && quote != '"' && quote != '`') {
        return 0;
    }
    // find the matching closing quote
    size_t i = 0, len = strlen(data);
    while (++i < len) {
        if (data[i] == quote) {
            if (data[i-1] == '\\') {
                if (quote != '\'') {
                    continue;
                }
            }
            return i;
        }
    }
    return 0;
}

/*
 * find the closing brace that matches the opening brace, which is the first
 * char of the data string.
 *
 * returns the zero-based index of the closing brace.. a return value of 0
 * means we didn't find the closing brace.
 */
size_t find_closing_brace(char* data) {
    // check the type of opening brace we have
    char opening_brace = data[0], closing_brace;
    if (opening_brace != '{' && opening_brace != '(') {
        return 0;
    }
    // determine the closing brace according to the opening brace
    if (opening_brace == '{') {
        closing_brace = '}';
    } else {
        closing_brace = ')';
    }
    // find the matching closing brace
    size_t ob_count = 1;
    size_t cb_count = 0;
    size_t i = 0;
    size_t len = strlen(data);
    while (++i < len) {
        if ((data[i] == '"') || (data[i] == '\'') || (data[i] == '`')) {
            // skip escaped quotes
            if(data[i-1] == '\\') {
                continue;
            }
            // skip quoted substrings
            char quote = data[i];
            while (++i < len) {
                if (data[i] == quote && data[i-1] != '\\') {
                    break;
                }
            }
            if (i == len) {
                return 0;
            }
            continue;
        }
        // keep the count of opening and closing braces
        if (data[i-1] != '\\') {
            if (data[i] == opening_brace) {
                ob_count++;
            } else if (data[i] == closing_brace) {
                cb_count++;
            }
        }
        // break when we have a matching number of opening and closing braces
        if (ob_count == cb_count) {
            break;
        }
    }
    if (ob_count != cb_count) {
        return 0;
    }
    return i;
}
