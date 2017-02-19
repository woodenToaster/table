#include <stdio.h>

#include "fct.h"
#include <string.h>

#include "cj_tbl.h"

FCT_BGN()
{
    {
        cj_tbl *t = NULL;
        FCT_FIXTURE_SUITE_BGN(simple)
        {
            FCT_SETUP_BGN()
            {
                t = cj_create_tbl();
            }
            FCT_SETUP_END();

            FCT_TEARDOWN_BGN()
            {
                if(t)
                {
                    free(t);
                    t = NULL;
                }
            }
            FCT_TEARDOWN_END();

            FCT_TEST_BGN(cj_create_tbl)
            {
                fct_chk(t != NULL);
            }
            FCT_TEST_END();

            FCT_TEST_BGN(array_assignment)
            {
                cj_arr_assign_int(t, 0, 1);
                int x = t->arr[0];
                fct_chk(x == 1);
            }
            FCT_TEST_END();

            FCT_TEST_BGN(array_retrieval)
            {
                t->arr[0] = 1;
                int x = cj_arr_get_int(t, 0);
                fct_chk(x == 1);
            }
            FCT_TEST_END();

            FCT_TEST_BGN(string_index)
            {
                cj_arr_assign_str(t, "my_key", 1);
                int val = cj_arr_get_str(t, "my_key");
                fct_chk(val == 1);
            }
            FCT_TEST_END();

            FCT_TEST_BGN(multiple_string_keys)
            {
                cj_arr_assign_str(t, "key1", 1);
                cj_arr_assign_str(t, "key2", 2);
                int val1 = cj_arr_get_str(t, "key1");
                int val2 = cj_arr_get_str(t, "key2");
                fct_chk(val1 == 1);
                fct_chk(val2 == 2);
            }
            FCT_TEST_END();

            // FCT_TEST_BGN()
            // {
                
            // }
            // FCT_TEST_END();

            FCT_TEST_BGN(cj_destory_tbl)
            {
                cj_destroy_tbl(&t);
                fct_chk(t == NULL);
            }
            FCT_TEST_END();
        }
        FCT_FIXTURE_SUITE_END();
    }
}
FCT_END();
