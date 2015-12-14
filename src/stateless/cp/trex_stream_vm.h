/*
 Itay Marom
 Cisco Systems, Inc.
*/

/*
Copyright (c) 2015-2015 Cisco Systems, Inc.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/
#ifndef __TREX_STREAM_VM_API_H__
#define __TREX_STREAM_VM_API_H__

#include <string>
#include <stdint.h>
#include <vector>
#include <unordered_map>
#include <assert.h>
#include <common/Network/Packet/IPHeader.h>



class StreamVm;


/* in memory program */

struct StreamDPOpFlowVar8 {
    uint8_t m_op;
    uint8_t m_flow_offset;
    uint8_t m_min_val;
    uint8_t m_max_val;
public:
    void dump(FILE *fd,std::string opt);

    inline void run_inc(uint8_t * flow_var) {
        uint8_t * p=(flow_var+m_flow_offset);
        *p=*p+1;
        if (*p>m_max_val) {
            *p=m_min_val;
        }
    }

    inline void run_dec(uint8_t * flow_var) {
        uint8_t * p=(flow_var+m_flow_offset);
        *p=*p-1;
        if (*p<m_min_val) {
            *p=m_max_val;
        }
    }

    inline void run_rand(uint8_t * flow_var) {
        uint8_t * p=(flow_var+m_flow_offset);
        *p= m_min_val + (rand() % (int)(m_max_val - m_min_val + 1));
    }


} __attribute__((packed)) ;

struct StreamDPOpFlowVar16 {
    uint8_t m_op;
    uint8_t m_flow_offset;
    uint16_t m_min_val;
    uint16_t m_max_val;
public:
    void dump(FILE *fd,std::string opt);

    inline void run_inc(uint8_t * flow_var) {
        uint16_t * p=(uint16_t *)(flow_var+m_flow_offset);
        *p=*p+1;
        if (*p>m_max_val) {
            *p=m_min_val;
        }
    }

    inline void run_dec(uint8_t * flow_var) {
        uint16_t * p=(uint16_t *)(flow_var+m_flow_offset);
        *p=*p-1;
        if (*p<m_min_val) {
            *p=m_max_val;
        }
    }

    inline void run_rand(uint8_t * flow_var) {
        uint16_t * p=(uint16_t *)(flow_var+m_flow_offset);
        *p= m_min_val + (rand() % (int)(m_max_val - m_min_val + 1));
    }



} __attribute__((packed)) ;

struct StreamDPOpFlowVar32 {
    uint8_t m_op;
    uint8_t m_flow_offset;
    uint32_t m_min_val;
    uint32_t m_max_val;
public:
    void dump(FILE *fd,std::string opt);

    inline void run_inc(uint8_t * flow_var) {
        uint32_t * p=(uint32_t *)(flow_var+m_flow_offset);
        *p=*p+1;
        if (*p>m_max_val) {
            *p=m_min_val;
        }
    }

    inline void run_dec(uint8_t * flow_var) {
        uint32_t * p=(uint32_t *)(flow_var+m_flow_offset);
        *p=*p-1;
        if (*p<m_min_val) {
            *p=m_max_val;
        }
    }

    inline void run_rand(uint8_t * flow_var) {
        uint32_t * p=(uint32_t *)(flow_var+m_flow_offset);
        *p= m_min_val + (rand() % (int)(m_max_val - m_min_val + 1));
    }

} __attribute__((packed)) ;

struct StreamDPOpFlowVar64 {
    uint8_t m_op;
    uint8_t m_flow_offset;
    uint64_t m_min_val;
    uint64_t m_max_val;
public:
    void dump(FILE *fd,std::string opt);

    inline void run_inc(uint8_t * flow_var) {
        uint64_t * p=(uint64_t *)(flow_var+m_flow_offset);
        *p=*p+1;
        if (*p>m_max_val) {
            *p=m_min_val;
        }
    }

    inline void run_dec(uint8_t * flow_var) {
        uint64_t * p=(uint64_t *)(flow_var+m_flow_offset);
        *p=*p-1;
        if (*p<m_min_val) {
            *p=m_max_val;
        }
    }

    inline void run_rand(uint8_t * flow_var) {
        uint64_t * p=(uint64_t *)(flow_var+m_flow_offset);
        *p= m_min_val + (rand() % (int)(m_max_val - m_min_val + 1));
    }


} __attribute__((packed)) ;


struct StreamDPOpPktWrBase {
    enum {
        PKT_WR_IS_BIG = 1
    }; /* for flags */

    uint8_t m_op;
    uint8_t m_flags;
    uint8_t  m_offset; 

public:
    bool is_big(){
        return ( (m_flags &StreamDPOpPktWrBase::PKT_WR_IS_BIG) == StreamDPOpPktWrBase::PKT_WR_IS_BIG ?true:false);
    }

} __attribute__((packed)) ;


struct StreamDPOpPktWr8 : public StreamDPOpPktWrBase {
    int8_t  m_val_offset;
    uint16_t m_pkt_offset;

public:
    void dump(FILE *fd,std::string opt);

    inline void wr(uint8_t * flow_var_base,uint8_t * pkt_base) {
        uint8_t * p_pkt      = (pkt_base+m_pkt_offset);
        uint8_t * p_flow_var = (flow_var_base+m_offset);
        *p_pkt=(*p_flow_var+m_val_offset);

    }


} __attribute__((packed)) ;


struct StreamDPOpPktWr16 : public StreamDPOpPktWrBase {
    uint16_t m_pkt_offset;
    int16_t  m_val_offset;
public:
    void dump(FILE *fd,std::string opt);

    inline void wr(uint8_t * flow_var_base,uint8_t * pkt_base) {
        uint16_t * p_pkt      = (uint16_t*)(pkt_base+m_pkt_offset);
        uint16_t * p_flow_var = (uint16_t*)(flow_var_base+m_offset);

        if ( likely(is_big())){
            *p_pkt=PKT_HTONS((*p_flow_var+m_val_offset));
        }else{
            *p_pkt=(*p_flow_var+m_val_offset);
        }

    }
} __attribute__((packed));

struct StreamDPOpPktWr32 : public StreamDPOpPktWrBase {
    uint16_t m_pkt_offset;
    int32_t  m_val_offset;
public:
    void dump(FILE *fd,std::string opt);

    inline void wr(uint8_t * flow_var_base,uint8_t * pkt_base) {
        uint32_t * p_pkt      = (uint32_t*)(pkt_base+m_pkt_offset);
        uint32_t * p_flow_var = (uint32_t*)(flow_var_base+m_offset);
        if ( likely(is_big())){
            *p_pkt=PKT_HTONL((*p_flow_var+m_val_offset));
        }else{
            *p_pkt=(*p_flow_var+m_val_offset);
        }
    }

} __attribute__((packed));

struct StreamDPOpPktWr64 : public StreamDPOpPktWrBase {
    uint16_t m_pkt_offset;
    int64_t  m_val_offset;

public:
    void dump(FILE *fd,std::string opt);

    inline void wr(uint8_t * flow_var_base,uint8_t * pkt_base) {
        uint64_t * p_pkt      = (uint64_t*)(pkt_base+m_pkt_offset);
        uint64_t * p_flow_var = (uint64_t*)(flow_var_base+m_offset);
        if ( likely(is_big())){
            *p_pkt=pal_ntohl64((*p_flow_var+m_val_offset));
        }else{
            *p_pkt=(*p_flow_var+m_val_offset);
        }
    }


} __attribute__((packed));

struct StreamDPOpIpv4Fix {
    uint8_t m_op;
    uint16_t  m_offset;
public:
    void dump(FILE *fd,std::string opt);
    void run(uint8_t * pkt_base){
        IPHeader *      ipv4=  (IPHeader *)(pkt_base+m_offset);
        ipv4->updateCheckSum();
    }

} __attribute__((packed));


/* datapath instructions */
class StreamDPVmInstructions {
public:
    enum INS_TYPE {
        ditINC8         ,
        ditINC16        ,
        ditINC32        ,
        ditINC64        ,

        ditDEC8         ,
        ditDEC16        ,
        ditDEC32        ,
        ditDEC64        ,

        ditRANDOM8      ,
        ditRANDOM16     ,
        ditRANDOM32     ,
        ditRANDOM64     ,

        ditFIX_IPV4_CS  ,

        itPKT_WR8       ,
        itPKT_WR16       ,
        itPKT_WR32       ,
        itPKT_WR64       
    };


public:
    void clear();
    void add_command(void *buffer,uint16_t size);
    uint8_t * get_program();
    uint32_t get_program_size();


    void Dump(FILE *fd);


private:
    std::vector<uint8_t> m_inst_list;
};


class StreamDPVmInstructionsRunner {
public:
    inline void run(uint32_t program_size,
                    uint8_t * program,  /* program */
                    uint8_t * flow_var, /* flow var */
                    uint8_t * pkt);      /* pkt */

};


inline void StreamDPVmInstructionsRunner::run(uint32_t program_size,
                                              uint8_t * program,  /* program */
                                              uint8_t * flow_var, /* flow var */
                                              uint8_t * pkt){


    uint8_t * p=program;
    uint8_t * p_end=p+program_size;


    union  ua_ {
        StreamDPOpFlowVar8  *lpv8;
        StreamDPOpFlowVar16 *lpv16;
        StreamDPOpFlowVar32 *lpv32;
        StreamDPOpFlowVar64 *lpv64;
        StreamDPOpIpv4Fix   *lpIpv4Fix;
        StreamDPOpPktWr8     *lpw8;
        StreamDPOpPktWr16    *lpw16;
        StreamDPOpPktWr32    *lpw32;
        StreamDPOpPktWr64    *lpw64;
    } ua ;

    while ( p < p_end) {
        uint8_t op_code=*p;
        switch (op_code) {

        case   StreamDPVmInstructions::ditINC8  :
            ua.lpv8 =(StreamDPOpFlowVar8 *)p;
            ua.lpv8->run_inc(flow_var);
            p+=sizeof(StreamDPOpFlowVar8);
            break;

        case  StreamDPVmInstructions::ditINC16  :
            ua.lpv16 =(StreamDPOpFlowVar16 *)p;
            ua.lpv16->run_inc(flow_var);
            p+=sizeof(StreamDPOpFlowVar16);
            break;
        case  StreamDPVmInstructions::ditINC32 :
            ua.lpv32 =(StreamDPOpFlowVar32 *)p;
            ua.lpv32->run_inc(flow_var);
            p+=sizeof(StreamDPOpFlowVar32);
             break;
        case  StreamDPVmInstructions::ditINC64 :
            ua.lpv64 =(StreamDPOpFlowVar64 *)p;
            ua.lpv64->run_inc(flow_var);
            p+=sizeof(StreamDPOpFlowVar64);
            break;

        case  StreamDPVmInstructions::ditDEC8 :
            ua.lpv8 =(StreamDPOpFlowVar8 *)p;
            ua.lpv8->run_dec(flow_var);
            p+=sizeof(StreamDPOpFlowVar8);
            break;
        case  StreamDPVmInstructions::ditDEC16 :
            ua.lpv16 =(StreamDPOpFlowVar16 *)p;
            ua.lpv16->run_dec(flow_var);
            p+=sizeof(StreamDPOpFlowVar16);
            break;
        case  StreamDPVmInstructions::ditDEC32 :
            ua.lpv32 =(StreamDPOpFlowVar32 *)p;
            ua.lpv32->run_dec(flow_var);
            p+=sizeof(StreamDPOpFlowVar32);
            break;
        case  StreamDPVmInstructions::ditDEC64 :
            ua.lpv64 =(StreamDPOpFlowVar64 *)p;
            ua.lpv64->run_dec(flow_var);
            p+=sizeof(StreamDPOpFlowVar64);
            break;

        case  StreamDPVmInstructions::ditRANDOM8 :
            ua.lpv8 =(StreamDPOpFlowVar8 *)p;
            ua.lpv8->run_rand(flow_var);
            p+=sizeof(StreamDPOpFlowVar8);
            break;
        case  StreamDPVmInstructions::ditRANDOM16 :
            ua.lpv16 =(StreamDPOpFlowVar16 *)p;
            ua.lpv16->run_rand(flow_var);
            p+=sizeof(StreamDPOpFlowVar16);
            break;
        case  StreamDPVmInstructions::ditRANDOM32 :
            ua.lpv32 =(StreamDPOpFlowVar32 *)p;
            ua.lpv32->run_rand(flow_var);
            p+=sizeof(StreamDPOpFlowVar32);
            break;
        case  StreamDPVmInstructions::ditRANDOM64 :
            ua.lpv64 =(StreamDPOpFlowVar64 *)p;
            ua.lpv64->run_rand(flow_var);
            p+=sizeof(StreamDPOpFlowVar64);
            break;

        case  StreamDPVmInstructions::ditFIX_IPV4_CS :
            ua.lpIpv4Fix =(StreamDPOpIpv4Fix *)p;
            ua.lpIpv4Fix->run(pkt);
            p+=sizeof(StreamDPOpIpv4Fix);
            break;

        case  StreamDPVmInstructions::itPKT_WR8  :
            ua.lpw8 =(StreamDPOpPktWr8 *)p;
            ua.lpw8->wr(flow_var,pkt);
            p+=sizeof(StreamDPOpPktWr8);
            break;

        case  StreamDPVmInstructions::itPKT_WR16 :
            ua.lpw16 =(StreamDPOpPktWr16 *)p;
            ua.lpw16->wr(flow_var,pkt);
            p+=sizeof(StreamDPOpPktWr16);
            break;

        case  StreamDPVmInstructions::itPKT_WR32 :
            ua.lpw32 =(StreamDPOpPktWr32 *)p;
            ua.lpw32->wr(flow_var,pkt);
            p+=sizeof(StreamDPOpPktWr32);
            break;

        case  StreamDPVmInstructions::itPKT_WR64 :      
            ua.lpw64 =(StreamDPOpPktWr64 *)p;
            ua.lpw64->wr(flow_var,pkt);
            p+=sizeof(StreamDPOpPktWr64);
            break;
        default:
            assert(0);
        }
    };
};




/**
 * interface for stream VM instruction
 * 
 */
class StreamVmInstruction {
public:

    enum INS_TYPE {
        itNONE         = 0,
        itFIX_IPV4_CS  = 4,
        itFLOW_MAN     = 5,
        itPKT_WR       = 6
    };

    typedef uint8_t instruction_type_t ;

    virtual instruction_type_t get_instruction_type()=0;

    virtual ~StreamVmInstruction();

    virtual void Dump(FILE *fd)=0;
    

private:
    static const std::string m_name;
};

/**
 * fix checksum for ipv4
 * 
 */
class StreamVmInstructionFixChecksumIpv4 : public StreamVmInstruction {
public:
    StreamVmInstructionFixChecksumIpv4(uint16_t offset) : m_pkt_offset(offset) {

    }

    virtual instruction_type_t get_instruction_type(){
        return ( StreamVmInstruction::itFIX_IPV4_CS);
    }

    virtual void Dump(FILE *fd);

public:
    uint16_t m_pkt_offset; /* the offset of IPv4 header from the start of the packet  */
};

/**
 * flow manipulation instruction
 * 
 * @author imarom (07-Sep-15)
 */
class StreamVmInstructionFlowMan : public StreamVmInstruction {

public:

    virtual instruction_type_t get_instruction_type(){
        return ( StreamVmInstruction::itFLOW_MAN);
    }

    /**
     * different types of operations on the object
     */
    enum flow_var_op_e {
        FLOW_VAR_OP_INC,
        FLOW_VAR_OP_DEC,
        FLOW_VAR_OP_RANDOM
    };

    StreamVmInstructionFlowMan(const std::string &var_name,
                               uint8_t size,
                               flow_var_op_e op,
                               uint64_t init_value,
                               uint64_t min_value,
                               uint64_t max_value) : 
                                                     m_var_name(var_name),
                                                     m_size_bytes(size),
                                                     m_op(op),
                                                     m_init_value(init_value),
                                                     m_min_value(min_value),
                                                     m_max_value(max_value) {

    }

    virtual void Dump(FILE *fd);

    void sanity_check(uint32_t ins_id,StreamVm *lp);

private:
    void sanity_check_valid_range(uint32_t ins_id,StreamVm *lp);
    void sanity_check_valid_size(uint32_t ins_id,StreamVm *lp);
    void sanity_check_valid_opt(uint32_t ins_id,StreamVm *lp);

public:


    /* flow var name */
    std::string   m_var_name;

    /* flow var size */
    uint8_t       m_size_bytes;

    /* type of op */
    flow_var_op_e m_op;

    /* range */
    uint64_t m_init_value;
    uint64_t m_min_value;
    uint64_t m_max_value;


};


class VmFlowVarRec {
public:
    uint32_t    m_offset;
    StreamVmInstructionFlowMan * m_instruction;
};




/**
 * write flow var to packet
 * 
 */
class StreamVmInstructionWriteToPkt : public StreamVmInstruction {
public:

    StreamVmInstructionWriteToPkt(const std::string &flow_var_name,
                                  uint16_t           pkt_offset,
                                  int32_t            add_value = 0,
                                  bool               is_big_endian = true) :

                                                        m_flow_var_name(flow_var_name),
                                                        m_pkt_offset(pkt_offset),
                                                        m_add_value(add_value),
                                                        m_is_big_endian(is_big_endian) {}

    virtual instruction_type_t get_instruction_type(){
        return ( StreamVmInstruction::itPKT_WR);
    }

    virtual void Dump(FILE *fd);

public:

    /* flow var name to write */
    std::string   m_flow_var_name;

    /* where to write */
    uint16_t      m_pkt_offset;

    /* add/dec value from field when writing */
    int32_t       m_add_value;

    /* writing endian */
    bool         m_is_big_endian;
};

/**
 * describes a VM program
 * 
 */
class StreamVm {
public:
    enum STREAM_VM {
        svMAX_FLOW_VAR   = 64, /* maximum flow varible */
        svMAX_PACKET_OFFSET_CHANGE = 512
    };



    StreamVm(){
        m_bss=0;
        m_pkt_size=0;
        m_cur_var_offset=0;
    }


    /* set packet size */
    void set_packet_size(uint16_t pkt_size){
        m_pkt_size = pkt_size;
    }

    uint16_t get_packet_size(){
        return ( m_pkt_size);
    }



    /**
     * add new instruction to the VM
     * 
     */
    void add_instruction(StreamVmInstruction *inst);

    /**
     * get const access to the instruction list
     * 
     */
    const std::vector<StreamVmInstruction *> & get_instruction_list();

    StreamDPVmInstructions  *           get_dp_instruction_buffer();

    uint16_t                                  get_bss_size(){
        return (m_cur_var_offset );
    }

    uint8_t *                                 get_bss_ptr(){
        return (m_bss );
    }


    uint16_t                                  get_max_packet_update_offset(){
        return ( m_max_field_update );
    }



    /**
     * compile the VM 
     * return true of success, o.w false 
     * 
     */
    bool compile();


    void compile_next();


    ~StreamVm();

    void Dump(FILE *fd);

    /* raise exception */
    void  err(const std::string &err);

private:

    /* lookup for varible offset, */
    bool var_lookup(const std::string &var_name,VmFlowVarRec & var);

    void  var_clear_table();

    bool  var_add(const std::string &var_name,VmFlowVarRec & var);

    uint16_t get_var_offset(const std::string &var_name);
    
    void build_flow_var_table() ;

    void build_bss();

    void build_program();

    void alloc_bss();

    void free_bss();

private:

    void clean_max_field_cnt();

    void add_field_cnt(uint16_t new_cnt);

private:
    uint16_t                           m_pkt_size;
    uint16_t                           m_cur_var_offset;
    uint16_t                           m_max_field_update; /* the location of the last byte that is going to be changed in the packet */ 

    std::vector<StreamVmInstruction *> m_inst_list;
    std::unordered_map<std::string, VmFlowVarRec> m_flow_var_offset;
    uint8_t *                          m_bss;

    StreamDPVmInstructions             m_instructions;
    
};

#endif /* __TREX_STREAM_VM_API_H__ */
