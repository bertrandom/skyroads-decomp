/* Native SkyRoads entry point. */
#include "compat.h"
#include "image_data.h"
#include <unistd.h>
#include <stdatomic.h>
#include <SDL.h>

void entry(void);
void hw_start(void);
void plat_run(int (*game_done)(void));

static atomic_int s_game_done;

static int game_thread(void *arg)
{
    (void)arg;
    entry();
    atomic_store(&s_game_done, 1);
    return 0;
}

static int game_done(void) { return atomic_load(&s_game_done); }

static int try_dir(const char *d)
{
    if (!d || chdir(d) != 0) return 0;
    if (access("ROADS.LZS", R_OK) == 0 || access("roads.lzs", R_OK) == 0) return 1;
    return 0;
}

/* Locate the original SkyRoads data files (ROADS.LZS, WORLD*.LZS, ...). */
static void find_data_dir(void)
{
    char buf[2048], cwd[1024];
    char *base = SDL_GetBasePath();     /* .app/Contents/Resources/ or exe dir */
    const char *rel[] = { "data", "Skyroads", "resources/Skyroads", "../resources/Skyroads",
                          "../../resources/Skyroads", NULL };
    int i;
    if (try_dir(getenv("SKYROADS_DATA"))) goto done;
    if (!getcwd(cwd, sizeof cwd)) cwd[0] = 0;
    if (try_dir(cwd)) goto done;
    for (i = 0; rel[i]; i++) {
        if (cwd[0]) { snprintf(buf, sizeof buf, "%s/%s", cwd, rel[i]); if (try_dir(buf)) goto done; }
        if (base)   { snprintf(buf, sizeof buf, "%s%s", base, rel[i]);  if (try_dir(buf)) goto done; }
    }
    fprintf(stderr, "SkyRoads: data files not found.\n"
                    "Put ROADS.LZS etc. next to the program (or in ./data), or set SKYROADS_DATA.\n");
    if (base) SDL_free(base);
    exit(1);
done:
    if (base) SDL_free(base);
}

int main(int argc, char **argv)
{
    (void)argc; (void)argv;
    {
        /* align the data segment (g_mem + DS_BASE) to 64 KiB in host memory */
        uint8_t *raw = (uint8_t *)calloc(1, MEM_SIZE + 0x20000);
        uintptr_t ds;
        if (!raw) { fprintf(stderr, "out of memory\n"); return 1; }
        ds = ((uintptr_t)raw + DS_BASE + 0xffff) & ~(uintptr_t)0xffff;
        g_mem = (uint8_t *)(ds - DS_BASE);
    }

    /* The unpacked program image lives at CS base 0x10000; the data segment
     * (DS_BASE 0x16760) is the tail of the same image. */
    memcpy(g_mem + CS_BASE, skyroads_image, sizeof(skyroads_image));
    g_ds = g_mem + DS_BASE;

    find_data_dir();
    if (plat_init() != 0) return 1;
    hw_start();
    SDL_CreateThread(game_thread, "game", NULL);
    plat_run(game_done);
    plat_shutdown();
    _exit(0);
}
