clean:
	rm -f **/*.o **/*.s **/out
	clang-format -i -style=file **/*.cpp **/*.h **/*.c

push:
	clang-format -i -style=file **/*.cpp **/*.h **/*.c
	git add .
	git commit -m "$m"
	git push origin main
