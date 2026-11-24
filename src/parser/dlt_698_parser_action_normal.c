#include "dlt_698_parser_private.h"
#include "dlt_698_parser_widget.h"

static int16_t dlt_698_parse_act_req_node(struct DLT_698_PRIVATE *ins_ptr, struct DLT_698_ACT_METHOD_PARA *act_ptr)
{
    act_ptr->next_index = 0;
    dlt_698_parse_omd(ins_ptr, &act_ptr->omd);
    // 解析数据信息
    uint8_t data_type = ins_ptr->_payld_ptr[ins_ptr->_payld_index++];
    dlt_698_parse_data(ins_ptr, data_type, &act_ptr->data);
    return DLT_698_ERR_NONE;
}
/*ACTION 请求*/
int16_t dlt_698_parse_act_req_normal(dlt_698_parser *parser)
{
    struct DLT_698_PRIVATE *ins_ptr = (struct DLT_698_PRIVATE *)parser->_ins;
    ins_ptr->frame.content.req_act = (struct DLT_698_ACT_NOR_REQ *)dlt_698_mempool_alloc(&ins_ptr->_mem, sizeof(struct DLT_698_ACT_NOR_REQ));
    if (ins_ptr->frame.content.req_act == NULL)
    {
        return DLT_698_ERR_EMPTY_PTR;
    }
    ins_ptr->frame.content.req_act->act_ptr = (struct DLT_698_ACT_METHOD_PARA *)dlt_698_mempool_alloc(&ins_ptr->_mem, sizeof(struct DLT_698_ACT_METHOD_PARA));
    if (ins_ptr->frame.content.req_act->act_ptr == NULL)
    {
        return DLT_698_ERR_EMPTY_PTR;
    }
    dlt_698_parse_act_req_node(ins_ptr, ins_ptr->frame.content.req_act->act_ptr);
    return DLT_698_ERR_NONE;
}
int16_t dlt_698_parse_act_req_normal_list(dlt_698_parser *parser)
{
    struct DLT_698_PRIVATE *ins_ptr = (struct DLT_698_PRIVATE *)parser->_ins;
    ins_ptr->frame.content.req_act = (struct DLT_698_ACT_NOR_REQ *)dlt_698_mempool_alloc(&ins_ptr->_mem, sizeof(struct DLT_698_ACT_NOR_REQ));
    if (ins_ptr->frame.content.req_act == NULL)
    {
        return DLT_698_ERR_EMPTY_PTR;
    }
    // 获取到SET GET个数
    uint8_t cnt = ins_ptr->_payld_ptr[ins_ptr->_payld_index++];
    ins_ptr->frame.content.req_act->act_ptr = NULL;
    struct DLT_698_ACT_METHOD_PARA **node_father = &ins_ptr->frame.content.req_act->act_ptr;
    for (int i = 0; i < cnt; i++)
    {
        uint16_t next_index = ins_ptr->_mem.alloc_mempool_size;
        struct DLT_698_ACT_METHOD_PARA *unit_ptr = (struct DLT_698_ACT_METHOD_PARA *)dlt_698_mempool_alloc(&ins_ptr->_mem, sizeof(struct DLT_698_ACT_METHOD_PARA));
        if (unit_ptr == NULL)
        {
            return DLT_698_ERR_EMPTY_PTR;
        }
        DLT_698_append_next(struct DLT_698_ACT_METHOD_PARA, ins_ptr->_mem.start, node_father, next_index);
        dlt_698_parse_act_req_node(ins_ptr, unit_ptr);
    }
    return DLT_698_ERR_NONE;
}

/*ACTION 响应*/
static int16_t dlt_698_parse_act_res_unit(struct DLT_698_PRIVATE *ins_ptr, struct DLT_698_ACT_METHOD_RESULT *result_ptr)
{
    result_ptr->next_index = 0;
    // OMD
    dlt_698_parse_omd(ins_ptr, &result_ptr->omd);
    // DAR
    result_ptr->DAR = ins_ptr->_payld_ptr[ins_ptr->_payld_index++];
    // //DATA信息，1=有效，0=无效
    uint8_t result = ins_ptr->_payld_ptr[ins_ptr->_payld_index++];
    uint8_t data_type = 0;    // 没有数据时按NULL解析
    if (1 == result)     // 有数据
    {
        data_type = ins_ptr->_payld_ptr[ins_ptr->_payld_index++];
    }

    // 解析数据信息
    dlt_698_parse_data(ins_ptr, data_type, &result_ptr->data);
    return DLT_698_ERR_NONE;
}
int16_t dlt_698_parse_act_res_normal(dlt_698_parser *parser)
{
    struct DLT_698_PRIVATE *ins_ptr = (struct DLT_698_PRIVATE *)parser->_ins;
    ins_ptr->frame.content.res_act = (struct DLT_698_ACT_NOR_RES *)dlt_698_mempool_alloc(&ins_ptr->_mem, sizeof(struct DLT_698_ACT_NOR_RES));
    if (ins_ptr->frame.content.res_act == NULL)
    {
        return DLT_698_ERR_EMPTY_PTR;
    }
    // 将结果存储区域结构化为DLT_698_ACT_NOR_RES_UNIT*形式
    ins_ptr->frame.content.res_act->result_ptr = (struct DLT_698_ACT_METHOD_RESULT *)dlt_698_mempool_alloc(&ins_ptr->_mem, sizeof(struct DLT_698_ACT_METHOD_RESULT));
    if (ins_ptr->frame.content.res_act->result_ptr == NULL)
    {
        return DLT_698_ERR_EMPTY_PTR;
    }
    return dlt_698_parse_act_res_unit(ins_ptr, ins_ptr->frame.content.res_act->result_ptr);
}
int16_t dlt_698_parse_act_res_normal_list(dlt_698_parser *parser)
{
    struct DLT_698_PRIVATE *ins_ptr = (struct DLT_698_PRIVATE *)parser->_ins;
    ins_ptr->frame.content.res_act = (struct DLT_698_ACT_NOR_RES *)dlt_698_mempool_alloc(&ins_ptr->_mem, sizeof(struct DLT_698_ACT_NOR_RES));
    if (ins_ptr->frame.content.res_act == NULL)
    {
        return DLT_698_ERR_EMPTY_PTR;
    }
    uint8_t cnt = ins_ptr->_payld_ptr[ins_ptr->_payld_index++];
    ins_ptr->frame.content.res_act->result_ptr = NULL;
    struct DLT_698_ACT_METHOD_RESULT **node_father = &ins_ptr->frame.content.res_act->result_ptr;
    for (int i = 0; i < cnt; i++)
    {
        int next_index = ins_ptr->_mem.alloc_mempool_size;
        struct DLT_698_ACT_METHOD_RESULT *unit_ptr = (struct DLT_698_ACT_METHOD_RESULT *)dlt_698_mempool_alloc(&ins_ptr->_mem, sizeof(struct DLT_698_ACT_METHOD_RESULT));
        if (unit_ptr == NULL)
        {
            return DLT_698_ERR_EMPTY_PTR;
        }
        DLT_698_append_next(struct DLT_698_ACT_METHOD_RESULT, ins_ptr->_mem.start, node_father, next_index);
        dlt_698_parse_act_res_unit(ins_ptr, unit_ptr);
    }
    return DLT_698_ERR_NONE;
}


/**
 * 请求ACTION 后 GET
 */
/*ActionThenGetRequestNormalList  设置并请求读取响应数据*/
static int16_t dlt_698_parse_act_get_req(struct DLT_698_PRIVATE *ins_ptr, struct DLT_698_ACT_GET_MOTHOD_PARA *act_ptr)
{
    dlt_698_parse_omd(ins_ptr, &act_ptr->act_omd);
    // 解析数据信息
    uint8_t data_type = ins_ptr->_payld_ptr[ins_ptr->_payld_index++];
    dlt_698_parse_data(ins_ptr, data_type, &act_ptr->data);
    // 解析读取的属性OAD
    dlt_698_parse_omd(ins_ptr, &act_ptr->get_oad);
    act_ptr->delay = ins_ptr->_payld_ptr[ins_ptr->_payld_index++];
    return DLT_698_ERR_NONE;
}
int16_t dlt_698_parse_act_get_req_normal_list(dlt_698_parser *parser)
{
    struct DLT_698_PRIVATE *ins_ptr = (struct DLT_698_PRIVATE *)parser->_ins;
    ins_ptr->frame.content.req_act_get = (struct DLT_698_ACT_GET_REQ *)dlt_698_mempool_alloc(&ins_ptr->_mem, sizeof(struct DLT_698_ACT_GET_REQ));
    if (ins_ptr->frame.content.req_act_get == NULL)
    {
        return DLT_698_ERR_EMPTY_PTR;
    }
    // 获取到ACT GET个数
    uint8_t cnt = ins_ptr->_payld_ptr[ins_ptr->_payld_index++];
    ins_ptr->frame.content.req_act_get->act_ptr = NULL;
    struct DLT_698_ACT_GET_MOTHOD_PARA **node_father = &ins_ptr->frame.content.req_act_get->act_ptr;
    for (int i = 0; i < cnt; i++)
    {
        int next_index = ins_ptr->_mem.alloc_mempool_size;
        struct DLT_698_ACT_GET_MOTHOD_PARA *unit_ptr = (struct DLT_698_ACT_GET_MOTHOD_PARA *)dlt_698_mempool_alloc(&ins_ptr->_mem, sizeof(struct DLT_698_ACT_GET_MOTHOD_PARA));
        if (unit_ptr == NULL)
        {
            return DLT_698_ERR_EMPTY_PTR;
        }
        DLT_698_append_next(struct DLT_698_ACT_GET_MOTHOD_PARA, ins_ptr->_mem.start, node_father, next_index);
        dlt_698_parse_act_get_req(ins_ptr, unit_ptr);
    }

    return DLT_698_ERR_NONE;
}
/**
 * 响应ACTION 后 GET
 */
/*ActionThenGetResponseNormalList  设置并请求读取响应数据*/
static int16_t dlt_698_parse_act_get_res(struct DLT_698_PRIVATE *ins_ptr, struct DLT_698_ACT_GET_MOTHOD_RESUlT *result_ptr)
{
    result_ptr->next_index = 0;
    /*ACT 响应数据*/
    dlt_698_parse_omd(ins_ptr, &result_ptr->act_omd);
    result_ptr->DAR = ins_ptr->_payld_ptr[ins_ptr->_payld_index++];
    // 结果信息，1=有效，0=无效
    uint8_t result = ins_ptr->_payld_ptr[ins_ptr->_payld_index++];
    uint8_t data_type = 0;    // 无数据时按NULL解析
    if (1 == result)
    {
        // 数据类型
        data_type = ins_ptr->_payld_ptr[ins_ptr->_payld_index++];
    }
    // 解析数据信息
    dlt_698_parse_data(ins_ptr, data_type, &result_ptr->get_data);
    dlt_698_parse_result_normal(ins_ptr, &result_ptr->result_normal);
    return DLT_698_ERR_NONE;
}
int16_t dlt_698_parse_act_get_res_normal_list(dlt_698_parser *parser)
{
    struct DLT_698_PRIVATE *ins_ptr = (struct DLT_698_PRIVATE *)parser->_ins;
    ins_ptr->frame.content.res_act_get = (struct DLT_698_ACT_GET_RES *)dlt_698_mempool_alloc(&ins_ptr->_mem, sizeof(struct DLT_698_ACT_GET_RES));
    if (ins_ptr->frame.content.res_act_get == NULL)
    {
        return DLT_698_ERR_EMPTY_PTR;
    }
    // 获取到ACT GET个数
    uint8_t cnt = ins_ptr->_payld_ptr[ins_ptr->_payld_index++];
    // 将结果存储区域结构化为DLT_698_ACT_GET_RES_NODE*形式
    ins_ptr->frame.content.res_act_get->result_ptr = NULL;
    struct DLT_698_ACT_GET_MOTHOD_RESUlT **node_father = &ins_ptr->frame.content.res_act_get->result_ptr;
    for (int i = 0; i < cnt; i++)
    {
        int next_index = ins_ptr->_mem.alloc_mempool_size;
        struct DLT_698_ACT_GET_MOTHOD_RESUlT *unit_ptr = (struct DLT_698_ACT_GET_MOTHOD_RESUlT *)dlt_698_mempool_alloc(&ins_ptr->_mem, sizeof(struct DLT_698_ACT_GET_MOTHOD_RESUlT));
        if (unit_ptr == NULL)
        {
            return DLT_698_ERR_EMPTY_PTR;
        }
        DLT_698_append_next(struct DLT_698_ACT_GET_MOTHOD_RESUlT, ins_ptr->_mem.start, node_father, next_index);
        dlt_698_parse_act_get_res(ins_ptr, unit_ptr);
    }

    return DLT_698_ERR_NONE;
}