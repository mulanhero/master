static int ltdl_pbc()
{
    int rc;
    char filename[1024];
    filename[0] = '\0';
    opal_lt_dladvise advise;

    if (!getenv("HAMSTER_HOME")) {
        opal_output(0, "ess:yarn:init: HAMSTER_HOME not set in env, please check.\n");
        return -1;
    }

    char* search_path = malloc(1024);
    strcpy(search_path, getenv("HAMSTER_HOME"));
    strcat(search_path, "/lib");

    if (opal_lt_dlinit() != 0) {
        opal_output(0, "LT_DLINIT FAILED - CANNOT LOAD LIBORTE");
        return -1;
    }

    /* open the library into the global namespace */
    if (opal_lt_dladvise_init(&advise)) {
        opal_output(0, "LT_DLADVISE INIT FAILED - CANNOT LOAD LIBORTE");
        return -1;
    }

    if (opal_lt_dladvise_ext(&advise)) {
        opal_output(0, "LT_DLADVISE EXT FAILED - CANNOT LOAD LIBORTE");
        opal_lt_dladvise_destroy(&advise);
        return -1;
    }

    if (opal_lt_dladvise_global(&advise)) {
        opal_output(0, "LT_DLADVISE GLOBAL FAILED - CANNOT LOAD LIBORTE");
        opal_lt_dladvise_destroy(&advise);
        return -1;
    }

    opal_lt_dlsetsearchpath(search_path);
    opal_output(2, "dlsearch path: %s.\n", opal_lt_dlgetsearchpath());

    /* load pbc lib */
    if (!opal_lt_dlopenadvise("libpbc", advise)) {
        free(search_path);
        opal_output(0, "ess:yarn:init: opal_lt_dlopenext for libpbc error: %s.\n", opal_lt_dlerror());
        return -1;
    }

    if (!opal_lt_dlopenadvise("libhdclient", advise)) {
        opal_output(0, "ess:yarn:init: opal_lt_dlopenext for libhdclient error: %s.\n", opal_lt_dlerror());
        return -1;
    }

    opal_lt_dladvise_destroy(&advise);

    return 0;
}
