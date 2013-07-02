#include <Python.h>

#include <openssl/ssl.h>
#include <openssl/rand.h>

#include "nassl_errors.h"
#include "nassl_SSL_CTX.h"
#include "nassl_SSL.h"
#include "nassl_BIO.h"
#include "nassl_X509.h"
#include "nassl_X509_EXTENSION.h"
#include "nassl_X509_NAME_ENTRY.h"




static PyMethodDef nassl_methods[] = {
    {NULL}  /* Sentinel */
};

#ifndef PyMODINIT_FUNC	/* declarations for DLL import/export */
#define PyMODINIT_FUNC void
#endif



PyMODINIT_FUNC init_nassl(void) {
    PyObject* m;

    // Initialize OpenSSL
    SSL_library_init();
    SSL_load_error_strings();

    // Check OpenSSL PRNG
    if(RAND_status() != 1) {
        PyErr_SetString(PyExc_EnvironmentError, "OpenSSL PRNG not seeded with enough data");
        return;
    }


    // Initalize the module
    m = Py_InitModule3("_nassl", nassl_methods,
                       "Example module that creates an extension type.");

    module_add_errors(m);
    module_add_SSL_CTX(m);
    module_add_SSL(m);
    module_add_BIO(m);
    module_add_X509(m);
    module_add_X509_EXTENSION(m);
    module_add_X509_NAME_ENTRY(m);

    if (PyErr_Occurred())
    {
        PyErr_SetString(PyExc_ImportError, "_nassl init failed");
    }

}