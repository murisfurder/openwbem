/*
 * perlProvider.cpp
 *
 * Copyright (c) 2002, International Business Machines
 *
 * THIS FILE IS PROVIDED UNDER THE TERMS OF THE COMMON PUBLIC LICENSE 
 * ("AGREEMENT"). ANY USE, REPRODUCTION OR DISTRIBUTION OF THIS FILE 
 * CONSTITUTES RECIPIENTS ACCEPTANCE OF THE AGREEMENT.
 *
 * You can obtain a current copy of the Common Public License from
 * http://oss.software.ibm.com/developerworks/opensource/license-cpl.html
 *
 * Author: Markus Mueller <markus_mueller@de.ibm.com>
 * Contributors:
 *
 * Description: <Some descriptive text>
 */

#include <unistd.h>
#include <stdio.h>

//#ifdef PERLIFC

#include "perlProvider.h"
#undef EXTERN_C

#include "npicrash.h"

#ifdef CRASH
#define CRASHHANDLE     void * __npichdl;
#define SETUPCRASHHANDLER    __npichdl=setupCrashHandler();
#define RESTORECRASHHANDLER  restoreCrashHandler(__npichdl);
#else
#define CRASHHANDLE     
#define SETUPCRASHHANDLER   
#define RESTORECRASHHANDLER  
#endif

#define INSTANCE_PROVIDER
#define ASSOCIATOR_PROVIDER
#define METHOD_PROVIDER
#define EVENT_PROVIDER
#include <provider.h>
#include <npi_import.h>

static inline int perl_strlen(const char * s)
{
   if (!s) return 0;
   else return strlen(s);
}


//PROVIDER_NAME(perlProvider)


EXTERN_C NPIEXPORT PerlFTABLE NPICALL perlProvider_initFunctionTable () {
   PerlFTABLE ftable = {
	  initialize, cleanup,
          _INCLUDE_INSTANCE_PROVIDER_METHODS
          _INCLUDE_ASSOCIATOR_PROVIDER_METHODS
          _INCLUDE_METHOD_PROVIDER_METHODS 
          _INCLUDE_EVENT_PROVIDER_METHODS
	  (PerlContext *)NULL
          }; 
      fprintf(stderr,"perlProvider: _initFunctionTable\n");
      return ftable;
  }

static char* setPath(NPIHandle *nh, char *path)
{
   char *e=getenv("NPIPERLPATH");

   if ((!nh) && (!nh->context))
   {
      fprintf(stderr,"--- ERROR context path not set\n");
      exit(0);
   }

   if (e==NULL) { 
      fprintf(stderr,"--- NPIPERLPATH environment not set\n");
      strcpy(path,"/usr/local/lib/openwbem/perlproviders/");
   }
   else 
      strcpy(path,e);

   strcat(path, ((PerlContext *)((NPIHandle *)nh->context))->scriptName);

   return path;
} 

static char * initialize ( NPIHandle *nh, CIMOMHandle ch)
{
    char *args[] = {"","","initialize"};
    int error;
    char msg[512],script[256];

    char * classList;

    PerlInterpreter * my_perl;

    fprintf(stderr,"--- perlProvider(): initialize\n");

    if ((args[1]=setPath(nh,script))==NULL) return;
       
    my_perl = perl_alloc();
    ((PerlContext *)((NPIHandle *)nh->context))->my_perl = (void *) my_perl;
    PERL_SET_CONTEXT(my_perl);
    perl_construct(my_perl);
    PL_exit_flags = 1;

    error=perl_parse(my_perl, xs_init, 2 , args, NULL);  
    if (error) {
       strcpy(msg,"Unable to load perl script: ");
       strcat(msg,script);
       raiseError(nh,msg);
       fprintf(stderr,"--- %s\n",msg);
       perl_destruct(my_perl);
       perl_free(my_perl);
    } 

    if (error) {
        nh->errorOccurred = -1;
        return NULL;
    }
    else
    {
        dSP;
        int count;
	SV * retval;
	STRLEN n_a;

        ENTER;
        SAVETMPS;

        PUSHMARK(SP);
        PUTBACK;

        /* count = call_pv("initialize", G_EVAL|G_DISCARD|G_NOARGS); */
        count = call_pv("initialize", G_EVAL|G_SCALAR|G_NOARGS);
            
        SPAGAIN;
        retval = POPs;
        classList = strdup(SvPV(retval, n_a));
	fprintf(stderr, "ClassList is %s, len %d\n", classList, n_a);
	if (n_a <= 1) {free(classList); classList = NULL;}

        PUTBACK;
        FREETMPS;
        LEAVE;
    }
    return classList;
}

static void cleanup (NPIHandle *nh)
{
    char * args[] = {"",NULL,"cleanup"};
    char script[256];
    PerlInterpreter * my_perl;

    args[1]=setPath(nh,script);
    my_perl = (PerlInterpreter *) (((PerlContext *)((NPIHandle *)nh->context))->my_perl);
    PERL_SET_CONTEXT(my_perl);

    /* cleanup perl */
    fprintf(stderr, "cleanup perl environment for library %s\n",args[1]);

    //perl_parse(my_perl, xs_init, 2 , args, NULL);
    {
        dSP;
        int count;

        ENTER;
        SAVETMPS;

        PUSHMARK(SP);
        PUTBACK;

        count = call_pv("cleanup", G_EVAL|G_DISCARD|G_NOARGS);
            
        SPAGAIN;

        PUTBACK;
        FREETMPS;
        LEAVE;
    }

    perl_destruct(my_perl);
    perl_free(my_perl);
    ((PerlContext *)((NPIHandle *)nh->context))->my_perl = (void *) NULL;
}

static Vector enumInstanceNames(NPIHandle *nh,CIMObjectPath cop,
                                int bool_deep,CIMClass cc)
{
    char * args[] = {"",NULL,"enumInstanceNames"};
    char script[256];
    PerlInterpreter * my_perl;

    Vector vec = {NULL};
    if (nh->errorOccurred) return vec;

    fprintf(stderr,"--- perlProvider(): enumInstanceNames\n");

    /* get name of perl executable */
    args[1]=setPath(nh,script);
    my_perl = (PerlInterpreter *) (((PerlContext *)((NPIHandle *)nh->context))->my_perl);
    PERL_SET_CONTEXT(my_perl);

    //perl_parse(my_perl, xs_init, 2 , args, NULL);
    {
        int count;
        SV * sva, * svb;
        char * ccc;

        // initialize local stack pointer
        dSP;

        ENTER;
        SAVETMPS;

        sva = sv_2mortal(newSVpv((char *)argsforperl(nh),10));
        svb = sv_2mortal(newSVpv((char *)argsforperl(vec.ptr),10));

        PUSHMARK(SP);

        // push the arguments on the stack
        XPUSHs(sva);
        XPUSHs(svb);
        XPUSHs(sv_2mortal(newSVpv((char *)argsforperl(cop.ptr),10)));
        XPUSHs(sv_2mortal(newSViv(-1)));
        XPUSHs(sv_2mortal(newSVpv((char *)argsforperl(cc.ptr),10)));

        // local stack pointer is global
        PUTBACK;

        count = call_pv("enumInstanceNames", G_EVAL|G_DISCARD);
            
        /* Retrieve second argument which should be the vector; */
        ccc = SvPV_nolen(svb);
        vec.ptr = argsfromperl(ccc);

        // back to the old stack pointer
        SPAGAIN;
        PUTBACK;

        FREETMPS;
        LEAVE;
    }
    if (vec.ptr == NULL) raiseError(nh,"No InstanceNames found"); 
    return vec;
}


static Vector enumInstances(NPIHandle *nh,CIMObjectPath cop,
                            int bool_deep,CIMClass cc,
                            int bool_localOnly)
{
    char * args[] = {"",NULL,"enumInstances"};
    char script[256];
    PerlInterpreter * my_perl;
    Vector      vec = {NULL};

    if (nh->errorOccurred) return vec;

    fprintf(stderr,"--- perlProvider(): enumInstances\n");

    /* get name of perl executable */
    args[1]=setPath(nh,script);
    my_perl = (PerlInterpreter *) (((PerlContext *)((NPIHandle *)nh->context))->my_perl);
    PERL_SET_CONTEXT(my_perl);

    //perl_parse(my_perl, xs_init, 2 , args, NULL);
    {
        dSP;
        int count;
        SV * sva;
        SV * svb;
        char * ccc;

        ENTER;
        SAVETMPS;

        sva = sv_2mortal(newSVpv((char *)argsforperl(nh),10));
        svb = sv_2mortal(newSVpv((char *)argsforperl(vec.ptr),10));

        PUSHMARK(SP);
        XPUSHs(sva);
        XPUSHs(svb);
        XPUSHs(sv_2mortal(newSVpv((char *)argsforperl(cop.ptr),10)));
        XPUSHs(sv_2mortal(newSViv(bool_deep)));
        /* XPUSHs(sv_2mortal(newSVpv(classname,perl_strlen(classname)))); */
        XPUSHs(sv_2mortal(newSVpv((char *)argsforperl(cc.ptr),10)));
        XPUSHs(sv_2mortal(newSViv(bool_localOnly)));
        PUTBACK;

        count = call_pv("enumInstances", G_EVAL|G_DISCARD);
            
        /* Retrieve second argument which should be the vector; */
        ccc = SvPV_nolen(svb);
        vec.ptr = argsfromperl(ccc);
            
        SPAGAIN;

        PUTBACK;
        FREETMPS;
        LEAVE;
    }
    if (vec.ptr == NULL) raiseError(nh,"No Instances found"); 
    return vec;
}

static CIMInstance getInstance(NPIHandle *nh,CIMObjectPath cop,CIMClass cc,
                               int bool_localOnly)
{
    char * args[] = {"",NULL,"getInstance"};
    char script[256];
    PerlInterpreter * my_perl;
    CIMInstance ci;

    fprintf(stderr,"--- perlProvider(): getInstance\n");

    /* get name of perl executable */
    args[1]=setPath(nh,script);
    my_perl = (PerlInterpreter *) (((PerlContext *)((NPIHandle *)nh->context))->my_perl);
    PERL_SET_CONTEXT(my_perl);

    //perl_parse(my_perl, xs_init, 2 , args, NULL);
    {
        dSP;
        int count;
        SV * sva;
        SV * svb;
        char * ccc;

        ENTER;
        SAVETMPS;

        ci.ptr=NULL;
        sva = sv_2mortal(newSVpv((char *)argsforperl(nh),10));
        svb = sv_2mortal(newSVpv((char *)argsforperl(ci.ptr),10));

        PUSHMARK(SP);
        XPUSHs(sva);
        XPUSHs(svb);
        XPUSHs(sv_2mortal(newSVpv((char *)argsforperl(cop.ptr),10)));
        XPUSHs(sv_2mortal(newSVpv((char *)argsforperl(cc.ptr),10)));
        XPUSHs(sv_2mortal(newSViv(bool_localOnly)));
        PUTBACK;

        count = call_pv("getInstance", G_EVAL|G_DISCARD);

        /* Retrieve second argument which should be the vector; */
        ccc = SvPV_nolen(svb);
        ci.ptr = argsfromperl(ccc);
            
        SPAGAIN;

        PUTBACK;
        FREETMPS;
        LEAVE;
    }
    if (ci.ptr==NULL) raiseError(nh,"Instance not found"); 
    return ci;
}


static CIMObjectPath createInstance(NPIHandle *nh, CIMObjectPath cop,
                                    CIMInstance ci)
{
    char * args[] = {"",NULL,"createInstance"};
    char script[256];
    PerlInterpreter * my_perl;
    CIMObjectPath newCop;

    fprintf(stderr,"--- perlProvider(): createInstance\n");

    /* get name of perl executable */
    args[1]=setPath(nh,script);
    my_perl = (PerlInterpreter *) (((PerlContext *)((NPIHandle *)nh->context))->my_perl);
    PERL_SET_CONTEXT(my_perl);

    //perl_parse(my_perl, xs_init, 2 , args, NULL);
    {
        dSP;
        int count;
        SV * sva;
        SV * svb;
        SV * svc;
        char * ccc;

        newCop.ptr=NULL;
        ENTER;
        SAVETMPS;

        sva = sv_2mortal(newSVpv((char *)argsforperl(nh),10));
        svb = sv_2mortal(newSVpv((char *)argsforperl(newCop.ptr),10));
        svc = sv_2mortal(newSVpv((char *)argsforperl(cop.ptr),10));

        PUSHMARK(SP);
        XPUSHs(sva);
        XPUSHs(svb);
        XPUSHs(svc);
        XPUSHs(sv_2mortal(newSVpv((char *)argsforperl(ci.ptr),10)));
        PUTBACK;

        count = call_pv("createInstance", G_EVAL|G_DISCARD);
            
        /* Retrieve second argument which should be the vector; */
        ccc = SvPV_nolen(svb);
        newCop.ptr = argsfromperl(ccc);
            
        SPAGAIN;

        PUTBACK;
        FREETMPS;
        LEAVE;
    }
    if (newCop.ptr==NULL) raiseError(nh,"Could not create Instance"); 
    return newCop;
}


static void setInstance(NPIHandle *nh,CIMObjectPath cop,CIMInstance ci)
{
    char * args[] = {"",NULL,"modifyInstance"};
    PerlInterpreter * my_perl;
    char script[256];

    fprintf(stderr,"--- perlProvider(): setInstance\n");

    /* get name of perl executable */
    args[1]=setPath(nh,script);
    my_perl = (PerlInterpreter *) (((PerlContext *)((NPIHandle *)nh->context))->my_perl);
    PERL_SET_CONTEXT(my_perl);

    //perl_parse(my_perl, xs_init, 2 , args, NULL);
    {
        dSP;
        int count;
        SV * sva;
        SV * svb;
        char * ccc;

        ENTER;
        SAVETMPS;

        sva = sv_2mortal(newSVpv((char *)argsforperl(nh),10));
        svb = sv_2mortal(newSVpv((char *)argsforperl(cop.ptr),10));

        PUSHMARK(SP);
        XPUSHs(sva);
        XPUSHs(svb);
        XPUSHs(sv_2mortal(newSVpv((char *)argsforperl(ci.ptr),10)));
        PUTBACK;

        count = call_pv("modifyInstance", G_EVAL|G_DISCARD);
            
        /* Retrieve second argument which should be the vector; */
        ccc = SvPV_nolen(svb);
        cop.ptr = argsfromperl(ccc);
            
        SPAGAIN;

        PUTBACK;
        FREETMPS;
        LEAVE;
    }
    return;
}


static void deleteInstance(NPIHandle *nh,CIMObjectPath cop)
{
    char * args[] = {"",NULL,"deleteInstance"};
    PerlInterpreter * my_perl;
    char script[256];

    fprintf(stderr,"--- perlProvider(): deleteInstance\n");

    /* get name of perl executable */
    args[1]=setPath(nh,script);
    my_perl = (PerlInterpreter *) (((PerlContext *)((NPIHandle *)nh->context))->my_perl);
    PERL_SET_CONTEXT(my_perl);

    {
        dSP;
        int count;
        SV * sva;
        SV * svb;
        char * ccc;

        ENTER;
        SAVETMPS;

        sva = sv_2mortal(newSVpv((char *)argsforperl(nh),10));
        svb = sv_2mortal(newSVpv((char *)argsforperl(cop.ptr),10));

        PUSHMARK(SP);
        XPUSHs(sva);
        XPUSHs(svb);
        PUTBACK;
        cop.ptr = NULL;

        count = call_pv("deleteInstance", G_EVAL|G_DISCARD);
            
        /* Retrieve second argument which should be the vector; */
        ccc = SvPV_nolen(svb);
        cop.ptr = argsfromperl(ccc);
            
        SPAGAIN;

        PUTBACK;
        FREETMPS;
        LEAVE;
    }
    return;
}


static Vector execQuery(NPIHandle *nh,CIMObjectPath cop,
                        const char * str,int i,CIMClass cc)
{
  return VectorNew(nh);
}

static Vector associators(NPIHandle *nh, CIMObjectPath assoc,
                          CIMObjectPath path,
                          const char * resultClass, const char *role,
                          const char * resultRole,
                          int includeQualifiers, int includeClassOrigin,
                          const char * propertyList[], int plLen)
{
    char * args[] = {"",NULL,"associators"};
    char script[256];
    PerlInterpreter * my_perl;
 
    Vector vec = {NULL};
    if (nh->errorOccurred) return vec;

    fprintf(stderr,"--- perlProvider(): associators\n");

    /* get name of perl executable */
    args[1]=setPath(nh,script);
    my_perl = (PerlInterpreter *) (((PerlContext *)((NPIHandle *)nh->context))->my_perl);
    PERL_SET_CONTEXT(my_perl);

    //perl_parse(my_perl, xs_init, 2, args, NULL);
    {
        dSP;
        int count;
        SV * sva;
        SV * svb;
        char * ccc;

        ENTER;
        SAVETMPS;

        sva = sv_2mortal(newSVpv((char *)argsforperl(nh),10));
        svb = sv_2mortal(newSVpv((char *)argsforperl(vec.ptr),10));

        PUSHMARK(SP);
        XPUSHs(sva);
        XPUSHs(svb);
        XPUSHs(sv_2mortal(newSVpv((char *)argsforperl(assoc.ptr),10)));
        XPUSHs(sv_2mortal(newSVpv((char *)argsforperl(path.ptr),10)));
	if (resultClass)
           XPUSHs(sv_2mortal(newSVpv(resultClass,perl_strlen(resultClass))));
	else
	   XPUSHs(sv_2mortal(newSVpv("",0)));
	if (role)
           XPUSHs(sv_2mortal(newSVpv(role,perl_strlen(role))));
	else
	   XPUSHs(sv_2mortal(newSVpv("",0)));
	if (resultRole)
           XPUSHs(sv_2mortal(newSVpv(resultRole,perl_strlen(resultRole))));
	else
	   XPUSHs(sv_2mortal(newSVpv("",0)));
        XPUSHs(sv_2mortal(newSViv(includeQualifiers)));
        XPUSHs(sv_2mortal(newSViv(includeClassOrigin)));
        PUTBACK;

        count = call_pv("associators", G_EVAL|G_DISCARD);

        /* Retrieve second argument which should be the vector; */
        ccc = SvPV_nolen(svb);
        vec.ptr = argsfromperl(ccc);

        SPAGAIN;

        PUTBACK;
        FREETMPS;
        LEAVE;
    }
    if (vec.ptr == NULL) raiseError(nh,"No Associations found"); 
    return vec;
}


static Vector associatorNames ( NPIHandle *nh , CIMObjectPath assoc,
                                CIMObjectPath path,
                                const char * resultClass,
                                const char * role, const char * resultRole)
{
    char * args[] = {"",NULL,"associatorNames"};
    char script[256];
    PerlInterpreter * my_perl;
 
    Vector vec = VectorNew(nh);
    if (nh->errorOccurred) return vec;

    fprintf(stderr,"--- perlProvider(): associatorNames\n");

    /* get name of perl executable */
    args[1]=setPath(nh,script);
    my_perl = (PerlInterpreter *) (((PerlContext *)((NPIHandle *)nh->context))->my_perl);
    PERL_SET_CONTEXT(my_perl);

    //perl_parse(my_perl, xs_init, 2, args, NULL);
    {
        dSP;
        int count;
        SV * sva;
        SV * svb;
        char * ccc;

        ENTER;
        SAVETMPS;

        sva = sv_2mortal(newSVpv((char *)argsforperl(nh),10));
        svb = sv_2mortal(newSVpv((char *)argsforperl(vec.ptr),10));

        PUSHMARK(SP);
        XPUSHs(sva);
        XPUSHs(svb);
        XPUSHs(sv_2mortal(newSVpv((char *)argsforperl(assoc.ptr),10)));
        XPUSHs(sv_2mortal(newSVpv((char *)argsforperl(path.ptr),10)));
	if (resultClass)
           XPUSHs(sv_2mortal(newSVpv(resultClass,perl_strlen(resultClass))));
	else
	   XPUSHs(sv_2mortal(newSVpv("",0)));
	if (role)
           XPUSHs(sv_2mortal(newSVpv(role,perl_strlen(role))));
	else
	   XPUSHs(sv_2mortal(newSVpv("",0)));
	if (resultRole)
           XPUSHs(sv_2mortal(newSVpv(resultRole,perl_strlen(resultRole))));
	else
	   XPUSHs(sv_2mortal(newSVpv("",0)));
        PUTBACK;

        count = call_pv("associatorNames", G_EVAL|G_DISCARD);

        /* Retrieve second argument which should be the vector; */
        ccc = SvPV_nolen(svb);
        vec.ptr = argsfromperl(ccc);

        SPAGAIN;

        PUTBACK;
        FREETMPS;
        LEAVE;
    }
    if (vec.ptr == NULL) raiseError(nh,"No AssociatorNames found"); 
    return vec;
}

static Vector references ( NPIHandle * nh, CIMObjectPath assoc,
                           CIMObjectPath path, const char * role,
                           int includeQualifiers, int includeClassOrigin,
                           const char * propertyList[], int plLen)
{
    char * args[] = {"",NULL,"references"};
    char script[256];
    PerlInterpreter * my_perl;
 
    Vector vec = VectorNew(nh);
    if (nh->errorOccurred) return vec;

    fprintf(stderr,"--- perlProvider(): references\n");

    /* get name of perl executable */
    args[1]=setPath(nh,script);
    my_perl = (PerlInterpreter *) (((PerlContext *)((NPIHandle *)nh->context))->my_perl);
    PERL_SET_CONTEXT(my_perl);

    //perl_parse(my_perl, xs_init, 2, args, NULL);
    {
        dSP;
        int count;
        SV * sva;
        SV * svb;
        char * ccc;

        ENTER;
        SAVETMPS;

        sva = sv_2mortal(newSVpv((char *)argsforperl(nh),10));
        svb = sv_2mortal(newSVpv((char *)argsforperl(vec.ptr),10));

        PUSHMARK(SP);
        XPUSHs(sva);
        XPUSHs(svb);
        XPUSHs(sv_2mortal(newSVpv((char *)argsforperl(assoc.ptr),10)));
        XPUSHs(sv_2mortal(newSVpv((char *)argsforperl(path.ptr),10)));
	if (role)
           XPUSHs(sv_2mortal(newSVpv(role,perl_strlen(role))));
	else
	   XPUSHs(sv_2mortal(newSVpv("",0)));
        XPUSHs(sv_2mortal(newSViv(includeQualifiers)));
        XPUSHs(sv_2mortal(newSViv(includeClassOrigin)));
        PUTBACK;

        count = call_pv("references", G_EVAL|G_DISCARD);

        /* Retrieve second argument which should be the vector; */
        ccc = SvPV_nolen(svb);
        vec.ptr = argsfromperl(ccc);

        SPAGAIN;

        PUTBACK;
        FREETMPS;
        LEAVE;
    }
    if (vec.ptr == NULL) raiseError(nh,"No References found"); 
    return vec;
}

static Vector referenceNames ( NPIHandle * nh, CIMObjectPath assoc,
                               CIMObjectPath path, const char * role)
{
    char * args[] = {"",NULL,"referenceNames"};
    char script[256];
    PerlInterpreter * my_perl;
 
    Vector vec = VectorNew(nh);
    if (nh->errorOccurred) return vec;

    fprintf(stderr,"--- perlProvider(): referenceNames\n");

    /* get name of perl executable */
    args[1]=setPath(nh,script);
    my_perl = (PerlInterpreter *) (((PerlContext *)((NPIHandle *)nh->context))->my_perl);
    PERL_SET_CONTEXT(my_perl);

    //perl_parse(my_perl, xs_init, 2, args, NULL);
    {
        dSP;
        int count;
        SV * sva;
        SV * svb;
        char * ccc;

        ENTER;
        SAVETMPS;

        sva = sv_2mortal(newSVpv((char *)argsforperl(nh),10));
        svb = sv_2mortal(newSVpv((char *)argsforperl(vec.ptr),10));

        PUSHMARK(SP);
        XPUSHs(sva);
        XPUSHs(svb);
        XPUSHs(sv_2mortal(newSVpv((char *)argsforperl(assoc.ptr),10)));
        XPUSHs(sv_2mortal(newSVpv((char *)argsforperl(path.ptr),10)));
	if (role)
           XPUSHs(sv_2mortal(newSVpv(role,perl_strlen(role))));
	else
	   XPUSHs(sv_2mortal(newSVpv("",0)));
        PUTBACK;

        count = call_pv("referenceNames", G_EVAL|G_DISCARD);

        /* Retrieve second argument which should be the vector; */
        ccc = SvPV_nolen(svb);
        vec.ptr = argsfromperl(ccc);

        SPAGAIN;

        PUTBACK;
        FREETMPS;
        LEAVE;
    }
    if (vec.ptr == NULL) raiseError(nh,"No ReferenceNames found"); 
    return vec;
}

 static CIMValue invokeMethod ( NPIHandle * nh, CIMObjectPath cop,
                                const char * a, Vector argsin, 
                                Vector argsout)
 {
     char * args[] = {"",NULL,"invokeMethod"};
     CIMValue cv = {NULL};

    char script[256];
    PerlInterpreter * my_perl;

    Vector vec = VectorNew(nh);
    if (nh->errorOccurred) return cv;

    fprintf(stderr,"--- perlProvider(): invokeMethod\n");

    /* get name of perl executable */
    args[1]=setPath(nh,script);
    my_perl = (PerlInterpreter *) (((PerlContext *)((NPIHandle *)nh->context))->my_perl);
    PERL_SET_CONTEXT(my_perl);

    //perl_parse(my_perl, xs_init, 2, args, NULL);
    {
		dSP;			// initialize perl stack pointer
        int count;	
        SV * sva;		// NpiHandle to pass to perl
        SV * svb;		
        
        char * ccc;
		char * cout;
		
        ENTER;			// everything created after here
        SAVETMPS;		// ...is a temporary variable. 

		/* set all parameters you need back... 
		returning values via parameter list is quite unperly...
		...we don't do this here */
		
        sva = sv_2mortal(newSVpv((char *)argsforperl(nh),10));
        svb = sv_2mortal(newSVpv((char *)argsforperl(vec.ptr),10));

        PUSHMARK(SP);	// remember the stack pointer 
        XPUSHs(sva);	// push the base onto the stack (NPIHandle)
        XPUSHs(svb);	// push the exponent onto the stack (NPIHandle)
		XPUSHs(sv_2mortal(newSVpv((char *)argsforperl(cop.ptr),10)));
		XPUSHs(sv_2mortal(newSVpv(a ,strlen(a))));		// push a onto stack (should be method name)
		XPUSHs(sv_2mortal(newSVpv((char *)argsforperl(argsin.ptr),10)));

		// do we need to mortalize argsout ??? 
		XPUSHs(sv_2mortal(newSVpv((char *)argsforperl(argsout.ptr),10)));
        PUTBACK;

        count = call_pv("invokeMethod", G_EVAL|G_ARRAY);

		SPAGAIN;

	    fprintf(stderr,"--- perlProvider(): invokeMethod: Got back %d values\n", count);
		if (count != 2)
            croak ("call_Inc: expected 2 value from 'invokeMethod', got %d\n",
                  count) ;

	/* Retrieve argsout arguments (first item in return list) */
	cout = POPp;
        /* Retrieve return value (second item in return list) */
        ccc = POPp;
        cv.ptr = argsfromperl(ccc);
	argsout.ptr=argsfromperl(cout);

        PUTBACK;
        FREETMPS;
        LEAVE;
    }
    if (cv.ptr == NULL) raiseError(nh,"invokeMethod returned NULL"); 
    return cv;
}

static void authorizeFilter( NPIHandle * nh, SelectExp exp,
                 const char * eventType, CIMObjectPath cop, const char * owner)
{
    fprintf(stderr,"--- perlProvider(): authorizeFilter\n");
    return;
}

static int mustPoll( NPIHandle * nh, SelectExp exp,
                 const char * eventType, CIMObjectPath cop)
{
    fprintf(stderr,"--- perlProvider(): mustPoll\n");
    return 0;
}


static void activateFilter( NPIHandle * nh, SelectExp exp,
                const char * eventType, CIMObjectPath cop, int firstActivation)
{
    char * args[] = {"",NULL,"activateFilter"};
    char script[256];
    PerlInterpreter * my_perl;
 
    fprintf(stderr,"--- perlProvider(): activateFilter\n");

    /* get name of perl executable */
    args[1]=setPath(nh,script);
    my_perl = (PerlInterpreter *) (((PerlContext *)((NPIHandle *)nh->context))->my_perl);
    PERL_SET_CONTEXT(my_perl);

    {
        dSP;
        int count;
        SV * sva;

        ENTER;
        SAVETMPS;

        sva = sv_2mortal(newSVpv((char *)argsforperl(nh),10));

        PUSHMARK(SP);
        XPUSHs(sva);
        XPUSHs(sv_2mortal(newSVpv((char *)argsforperl(exp.ptr),10)));
	if (eventType)
           XPUSHs(sv_2mortal(newSVpv(eventType,perl_strlen(eventType))));
	else
	   XPUSHs(sv_2mortal(newSVpv("",0)));
        XPUSHs(sv_2mortal(newSVpv((char *)argsforperl(cop.ptr),10)));
        XPUSHs(sv_2mortal(newSViv(firstActivation)));
        PUTBACK;

        count = call_pv("activateFilter", G_EVAL|G_DISCARD);

        /* Retrieve second argument which should be the vector; */
        //ccc = SvPV_nolen(svb);
        //vec.ptr = argsfromperl(ccc);

        SPAGAIN;

        PUTBACK;
        FREETMPS;
        LEAVE;
    }
    //if (vec.ptr == NULL) raiseError(nh,"No ReferenceNames found"); 
    return;
}

static void deActivateFilter( NPIHandle * nh, SelectExp exp,
                 const char * eventType, CIMObjectPath cop, int lastActivation)
{
    char * args[] = {"",NULL,"deactivateFilter"};
    char script[256];
    PerlInterpreter * my_perl;
 
    fprintf(stderr,"--- perlProvider(): deactivateFilter\n");

    /* get name of perl executable */
    args[1]=setPath(nh,script);
    my_perl = (PerlInterpreter *) (((PerlContext *)((NPIHandle *)nh->context))->my_perl);
    PERL_SET_CONTEXT(my_perl);

    {
        dSP;
        int count;
        SV * sva;

        ENTER;
        SAVETMPS;

        sva = sv_2mortal(newSVpv((char *)argsforperl(nh),10));

        PUSHMARK(SP);
        XPUSHs(sva);
        XPUSHs(sv_2mortal(newSVpv((char *)argsforperl(exp.ptr),10)));
	if (eventType)
           XPUSHs(sv_2mortal(newSVpv(eventType,perl_strlen(eventType))));
	else
	   XPUSHs(sv_2mortal(newSVpv("",0)));
        XPUSHs(sv_2mortal(newSVpv((char *)argsforperl(cop.ptr),10)));
        XPUSHs(sv_2mortal(newSViv(lastActivation)));
        PUTBACK;

        count = call_pv("deactivateFilter", G_EVAL|G_DISCARD);

        /* Retrieve second argument which should be the vector; */
        //ccc = SvPV_nolen(svb);
        //vec.ptr = argsfromperl(ccc);

        SPAGAIN;

        PUTBACK;
        FREETMPS;
        LEAVE;
    }
    //if (vec.ptr == NULL) raiseError(nh,"No ReferenceNames found"); 
    return;
}
//#endif
