
RM?=rm -f
PKGCONFIG?=pkg-config
PKGS?=sdl2

LIBEXT?=.a
BINEXT?=
OBJEXT?=.o

CFLAGS+=-m32 -std=c23 $(shell $(PKGCONFIG) $(PKGS) --cflags)
LDFLAGS+=-m32 $(shell $(PKGCONFIG) $(PKGS) --libs) -lm

ifeq ($(PARANOID),1)
CFLAGS+=-Wall -Wextra
endif

LIBNAME?=libsdl3quake$(LIBEXT)
EXECNAME?=sdl3quake$(BINEXT)

LIBOBJS =\
	cd_null$(OBJEXT) chase$(OBJEXT) cl_demo$(OBJEXT) cl_input$(OBJEXT)\
	cl_main$(OBJEXT) cl_parse$(OBJEXT) cl_tent$(OBJEXT) cmd$(OBJEXT)\
	common$(OBJEXT) console$(OBJEXT) crc$(OBJEXT) cvar$(OBJEXT)\
	d_edge$(OBJEXT) d_fill$(OBJEXT) d_init$(OBJEXT) d_modech$(OBJEXT)\
	d_part$(OBJEXT) d_polyse$(OBJEXT) d_scan$(OBJEXT) d_sky$(OBJEXT)\
	d_sprite$(OBJEXT) d_surf$(OBJEXT) d_vars$(OBJEXT) d_zpoint$(OBJEXT)\
	draw$(OBJEXT) host_cmd$(OBJEXT) host$(OBJEXT) in_null$(OBJEXT)\
	keys$(OBJEXT) mathlib$(OBJEXT) menu$(OBJEXT) model$(OBJEXT)\
	net_loop$(OBJEXT) net_main$(OBJEXT) net_none$(OBJEXT) pr_cmds$(OBJEXT)\
	pr_edict$(OBJEXT) pr_exec$(OBJEXT) r_aclip$(OBJEXT) r_alias$(OBJEXT)\
	r_bsp$(OBJEXT) r_draw$(OBJEXT) r_edge$(OBJEXT) r_efrag$(OBJEXT)\
	r_light$(OBJEXT) r_main$(OBJEXT) r_misc$(OBJEXT) r_part$(OBJEXT)\
	r_sky$(OBJEXT) r_sprite$(OBJEXT) r_surf$(OBJEXT) r_vars$(OBJEXT)\
	sbar$(OBJEXT) screen$(OBJEXT) snd_null$(OBJEXT) sv_main$(OBJEXT)\
	sv_move$(OBJEXT) sv_phys$(OBJEXT) sv_user$(OBJEXT) sys_null$(OBJEXT)\
	vid_null$(OBJEXT) view$(OBJEXT) wad$(OBJEXT) world$(OBJEXT)\
	zone$(OBJEXT) libsdl3quake$(OBJEXT)

EXECOBJS=sdl3quake$(OBJEXT)

all: $(LIBNAME) $(EXECNAME)

clean:
	$(RM) $(LIBNAME) $(EXECNAME) $(LIBOBJS) $(EXECOBJS)

debug: CFLAGS+=-g -O0 -DDEBUG
debug: $(LIBNAME)
debug: $(EXECNAME)

release: CFLAGS+=-O3 -DNDEBUG
release: $(LIBNAME)
release: $(EXECNAME)

$(EXECNAME): $(LIBNAME) $(EXECOBJS)
	$(CC) -o $@ $(EXECOBJS) $(LIBNAME) $(LDFLAGS)

$(LIBNAME): $(LIBOBJS)
	$(AR) rcs $@ $(LIBOBJS)
