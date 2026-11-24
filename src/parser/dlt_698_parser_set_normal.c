#include "dlt_698_parser_set_normal.h"
#include "dlt_698_parser_private.h"
#include "dlt_698_parser_widget.h"
// 解析SET请求的数据单元
static int16_t dlt_698_parse_set_req_normal_unit(struct DLT_698_PRIVATE *ins_ptr, struct DLT_698_SET_ATTRIBUTE *unit_ptr)
{
    unit_ptr->next_index = 0;
    // 解析OAD
    int16_t ret = dlt_698_parse_oad(ins_ptr, &unit_ptr->oad);
    if (ret != DLT_698_ERR_NONE)
    {
        return ret;
    }
    uint8_t data_type = 0;
    ret = dlt_698_payld_read_u8(ins_ptr, &data_type);
    if (ret != DLT_698_ERR_NONE)
    {
        return ret;
    }
    // 解析数据信息
    return dlt_698_parse_data(ins_ptr, data_type, &unit_ptr->data);
}
/*解析SET NORMAL 请求*/
int16_t dlt_698_parse_set_req_normal(dlt_698_parser *parser)
{
    struct DLT_698_PRIVATE *ins_ptr = (struct DLT_698_PRIVATE *)parser->_ins;
    ins_ptr->frame.content.req_set = (struct DLT_698_SET_NOR_REQ *)dlt_698_mempool_alloc(&ins_ptr->_mem, sizeof(struct DLT_698_SET_NOR_REQ));
    if (ins_ptr->frame.content.req_set == NULL)
    {
        return DLT_698_ERR_MEM;
    }
    // 向内存池申请一个struct DLT_698_SET_NOR_REQ_NODE
    ins_ptr->frame.content.req_set->set_ptr = (struct DLT_698_SET_ATTRIBUTE *)dlt_698_mempool_alloc(&ins_ptr->_mem, sizeof(struct DLT_698_SET_ATTRIBUTE));
    if (ins_ptr->frame.content.req_set->set_ptr == NULL)
    {
        return DLT_698_ERR_MEM;
    }
    return dlt_698_parse_set_req_normal_unit(ins_ptr, ins_ptr->frame.content.req_set->set_ptr);
}
/*解析SET NORMAL 请求 LIST*/
int16_t dlt_698_parse_set_req_normal_list(dlt_698_parser *parser)
{
    struct DLT_698_PRIVATE *ins_ptr = (struct DLT_698_PRIVATE *)parser->_ins;
    ins_ptr->frame.content.req_set = (struct DLT_698_SET_NOR_REQ *)dlt_698_mempool_alloc(&ins_ptr->_mem, sizeof(struct DLT_698_SET_NOR_REQ));
    if (ins_ptr->frame.content.req_set == NULL)
    {
        return DLT_698_ERR_MEM;
    }
    // 获取到SET个数
    uint8_t set_cnt = 0;
    int16_t ret = dlt_698_payld_read_u8(ins_ptr, &set_cnt);
    if (ret != DLT_698_ERR_NONE)
    {
        return ret;
    }
    ins_ptr->frame.content.req_set->set_ptr = NULL;
    struct DLT_698_SET_ATTRIBUTE **node_father = &ins_ptr->frame.content.req_set->set_ptr;
    for (int i = 0; i < set_cnt; i++)
    {
        uint16_t next_index = ins_ptr->_mem.alloc_mempool_size;
        struct DLT_698_SET_ATTRIBUTE *node_ptr = (struct DLT_698_SET_ATTRIBUTE *)dlt_698_mempool_alloc(&ins_ptr->_mem, sizeof(struct DLT_698_SET_ATTRIBUTE));
        if (!node_ptr)
        {
            return DLT_698_ERR_MEM;
        }
        DLT_698_append_next(struct DLT_698_SET_ATTRIBUTE, ins_ptr->_mem.start, node_father, next_index);
        ret = dlt_698_parse_set_req_normal_unit(ins_ptr, node_ptr);
        if (ret != DLT_698_ERR_NONE)
        {
            return ret;
        }
    }
    return DLT_698_ERR_NONE;
}

/*SET NORMAL 响应*/

static int16_t dlt_698_parse_set_res_normal_unit(struct DLT_698_PRIVATE *ins_ptr, struct DLT_698_SET_RESULT *unit_ptr)
{
    unit_ptr->next_index = 0;
    int16_t ret = dlt_698_parse_oad(ins_ptr, &unit_ptr->oad);
    if (ret != DLT_698_ERR_NONE)
    {
        return ret;
    }
    return dlt_698_payld_read_u8(ins_ptr, &unit_ptr->DAR);
}

/*解析SET NORMAL 响应*/
int16_t dlt_698_parse_set_res_normal(dlt_698_parser *parser)
{
    struct DLT_698_PRIVATE *ins_ptr = (struct DLT_698_PRIVATE *)parser->_ins;
    ins_ptr->frame.content.res_set = (struct DLT_698_SET_NOR_RES *)dlt_698_mempool_alloc(&ins_ptr->_mem, sizeof(struct DLT_698_SET_NOR_RES));
    if (ins_ptr->frame.content.res_set == NULL)
    {
        return DLT_698_ERR_MEM;
    }
    ins_ptr->frame.content.res_set->result_ptr = (struct DLT_698_SET_RESULT *)dlt_698_mempool_alloc(&ins_ptr->_mem, sizeof(struct DLT_698_SET_RESULT));
    if (ins_ptr->frame.content.res_set->result_ptr == NULL)
    {
        return DLT_698_ERR_MEM;
    }
    return dlt_698_parse_set_res_normal_unit(ins_ptr, ins_ptr->frame.content.res_set->result_ptr);
}
/*解析SET NORMAL 响应 LIST*/
int16_t dlt_698_parse_set_res_normal_list(dlt_698_parser *parser)
{
    struct DLT_698_PRIVATE *ins_ptr = (struct DLT_698_PRIVATE *)parser->_ins;
    ins_ptr->frame.content.res_set = (struct DLT_698_SET_NOR_RES *)dlt_698_mempool_alloc(&ins_ptr->_mem, sizeof(struct DLT_698_SET_NOR_RES));
    if (ins_ptr->frame.content.res_set == NULL)
    {
        return DLT_698_ERR_MEM;
    }
    // 获取到SET个数
    uint8_t set_cnt = 0;
    int16_t ret = dlt_698_payld_read_u8(ins_ptr, &set_cnt);
    if (ret != DLT_698_ERR_NONE)
    {
        return ret;
    }
    ins_ptr->frame.content.res_set->result_ptr = NULL;
    struct DLT_698_SET_RESULT **node_father = &ins_ptr->frame.content.res_set->result_ptr;
    for (int i = 0; i < set_cnt; i++)
    {

        uint16_t next_index = ins_ptr->_mem.alloc_mempool_size;
        struct DLT_698_SET_RESULT *node_ptr = (struct DLT_698_SET_RESULT *)dlt_698_mempool_alloc(&ins_ptr->_mem, sizeof(struct DLT_698_SET_RESULT));
        if (!node_ptr)
        {
            return DLT_698_ERR_MEM;
        }
        DLT_698_append_next(struct DLT_698_SET_RESULT, ins_ptr->_mem.start, node_father, next_index);
        ret = dlt_698_parse_set_res_normal_unit(ins_ptr, node_ptr);
        if (ret != DLT_698_ERR_NONE)
        {
            return ret;
        }
    }
    return DLT_698_ERR_NONE;
}

/*SetThenGetRequestNormalList  设置并请求读取响应数据*/
static int16_t dlt_698_parse_set_get_req(struct DLT_698_PRIVATE *ins_ptr, struct DLT_698_SET_GET_ATTRIBUTE *set_ptr)
{
    // 解析OAD
    int16_t ret = dlt_698_parse_oad(ins_ptr, &set_ptr->set_oad);
    if (ret != DLT_698_ERR_NONE)
    {
        return ret;
    }
    // 解析数据信息
    uint8_t data_type = 0;
    ret = dlt_698_payld_read_u8(ins_ptr, &data_type);
    if (ret != DLT_698_ERR_NONE)
    {
        return ret;
    }
    ret = dlt_698_parse_data(ins_ptr, data_type, &set_ptr->set_data);
    if (ret != DLT_698_ERR_NONE)
    {
        return ret;
    }
    // 解析读取的属性OAD
    ret = dlt_698_parse_oad(ins_ptr, &set_ptr->get_oad);
    if (ret != DLT_698_ERR_NONE)
    {
        return ret;
    }
    return dlt_698_payld_read_u8(ins_ptr, &set_ptr->delay);
}
int16_t dlt_698_parse_set_get_req_normal_list(dlt_698_parser *parser)
{
    struct DLT_698_PRIVATE *ins_ptr = (struct DLT_698_PRIVATE *)parser->_ins;
    ins_ptr->frame.content.req_set_get = (struct DLT_698_SET_GET_REQ *)dlt_698_mempool_alloc(&ins_ptr->_mem, sizeof(struct DLT_698_SET_GET_REQ));
    if (ins_ptr->frame.content.req_set_get == NULL)
    {
        return DLT_698_ERR_MEM;
    }
    uint8_t cnt = 0;
    int16_t ret = dlt_698_payld_read_u8(ins_ptr, &cnt);
    if (ret != DLT_698_ERR_NONE)
    {
        return ret;
    }
    ins_ptr->frame.content.req_set_get->set_ptr = NULL;
    struct DLT_698_SET_GET_ATTRIBUTE **node_father = &ins_ptr->frame.content.req_set_get->set_ptr;
    for (int i = 0; i < cnt; i++)
    {
        uint16_t next_index = ins_ptr->_mem.alloc_mempool_size;
        struct DLT_698_SET_GET_ATTRIBUTE *node_ptr = (struct DLT_698_SET_GET_ATTRIBUTE *)dlt_698_mempool_alloc(&ins_ptr->_mem, sizeof(struct DLT_698_SET_GET_ATTRIBUTE));
        if (!node_ptr)
        {
            return DLT_698_ERR_MEM;
        }
        DLT_698_append_next(struct DLT_698_SET_GET_ATTRIBUTE, ins_ptr->_mem.start, node_father, next_index);
        ret = dlt_698_parse_set_get_req(ins_ptr, node_ptr);
        if (ret != DLT_698_ERR_NONE)
        {
            return ret;
        }
    }
    return DLT_698_ERR_NONE;
}

/*SetThenGetResponseNormalList  设置并请求读取响应数据*/
static int16_t dlt_698_parse_set_get_res(struct DLT_698_PRIVATE *ins_ptr, struct DLT_698_SET_GET_RESULT *result_ptr)
{
    /*SET 响应数据*/
    int16_t ret = dlt_698_parse_oad(ins_ptr, &result_ptr->set_oad);
    if (ret != DLT_698_ERR_NONE)
    {
        return ret;
    }
    ret = dlt_698_payld_read_u8(ins_ptr, &result_ptr->DAR);
    if (ret != DLT_698_ERR_NONE)
    {
        return ret;
    }
    /*GET 响应数据*/
    return dlt_698_parse_result_normal(ins_ptr, &result_ptr->result_nornaml);
}
int16_t dlt_698_parse_set_get_res_normal_list(dlt_698_parser *parser)
{
    struct DLT_698_PRIVATE *ins_ptr = (struct DLT_698_PRIVATE *)parser->_ins;
    ins_ptr->frame.content.res_set_get = (struct DLT_698_SET_GET_RES *)dlt_698_mempool_alloc(&ins_ptr->_mem, sizeof(struct DLT_698_SET_GET_RES));
    if (ins_ptr->frame.content.res_set_get == NULL)
    {
        return DLT_698_ERR_MEM;
    }
    // 获取到SET GET个数
    uint8_t cnt = 0;
    int16_t ret = dlt_698_payld_read_u8(ins_ptr, &cnt);
    if (ret != DLT_698_ERR_NONE)
    {
        return ret;
    }
    // 将结果存储区域结构化为DLT_698_SET_GET_RES_NODE*形式
    ins_ptr->frame.content.res_set_get->result_ptr = NULL;
    struct DLT_698_SET_GET_RESULT **node_father = &ins_ptr->frame.content.res_set_get->result_ptr;
    for (int i = 0; i < cnt; i++)
    {
        uint16_t next_index = ins_ptr->_mem.alloc_mempool_size;
        struct DLT_698_SET_GET_RESULT *node_ptr = (struct DLT_698_SET_GET_RESULT *)dlt_698_mempool_alloc(&ins_ptr->_mem, sizeof(struct DLT_698_SET_GET_RESULT));
        if (!node_ptr)
        {
            return DLT_698_ERR_MEM;
        }
        DLT_698_append_next(struct DLT_698_SET_GET_RESULT, ins_ptr->_mem.start, node_father, next_index);
        ret = dlt_698_parse_set_get_res(ins_ptr, node_ptr);
        if (ret != DLT_698_ERR_NONE)
        {
            return ret;
        }
    }
    return DLT_698_ERR_NONE;
}
