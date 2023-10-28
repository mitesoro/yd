dev:
	rsync -avzP --delete --exclude-from=makefile.excludes ./ ubuntu@101.34.210.69:/home/ubuntu/work/
.PHONY : dev