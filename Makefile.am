SUBDIRS = . src scripts tests
EXTRA_DIST=.clang-format .gitignore .valgrindrc README.md

performance:
	sudo sh -c "echo 0 > /proc/sys/kernel/randomize_va_space"
	sudo sh $(top_srcdir)/scripts/performance.sh

plot: all
	$(top_srcdir)/scripts/plot_spend_time.sh

plotclean:
	$(RM) -rf plot
