Content-Type: text/x-zim-wiki  
Wiki-Format: zim 0.4  
Creation-Date: 2013-11-12T18:34:15-08:00  
  
# Git  
Created Tuesday 12 November 2013  
  
**Repository -** Database containing complete files/version/revision history.   
**Workspace -** Local working area. Does not effect repository  
**Commit -** Push workspace to repository  
**Conflict -** Two developers make conflicting commits, VCS generates a conflict to be manually resolved  
**Merge -** Combining multiple changes from different working copies. Most VCS automatically merge most files  
**Branch -** A tangential line of development for things like new features and bug fixing  
  
--Types of version control--  
	__Local Version Control__  
		* Allows for pushing/commiting/pulling from a local file.  
  
	__Centralized Version Control__  
		(example: SVN)  
		  
	__Distributed Version Control__  
		* Everyone has a local copy, people can grab others' copies directly. Main copies stored on server. (ex/ GIT)  
  
  
  
--Workflow--  
1) __INITIALIZE A REPOSITORY__  
  
	*git status *- gives status about the directory you are currently in, also lists modified files.  
	*git init . *- initializes an empty git repository in the current directory  
	  
	**Untracked Files -** Files inside of a git directory that aren't inside of the repository  
  
2)__ FIRST COMMIT__  
  
	*git add <fileName> *- Adds a file to the pending commits, accepts wildcards  
	*git commit *- commits all pending commits to the repository  
		*-m "message" *- allows for adding an inline commit message  
		*-a - *Automatically commits all modified files  
		*-am - *Automatically commits all modified files with inline commit message  
		  
	**Keep in mind that you are commiting to a local repository. All repositories are local unless using some sort of server (BitBucket, Github, etc..)**  
  
3) __MAKE CHANGES__  
  
	*git diff <fileName> *- Gets an easy-to-read list of differences between the local copy and repository copy  
	*git commit -am <message>*  
	  
4) __UNDOING THINGS__  
	  
	*git reset --hard HEAD *- Resets all files within the directory (linked with git) to the last (HEAD) commit.  
  
5) __TIME TRAVEL!__  
	  
	*git log *- Allows you to see a history of the commits on the directory  
	*git reset --hard <hash> *- Allows you to reset to a specific commit (The hash can be seen within the log)  
	*git checkout <branchOptions> - *Allows you to checkout certain parts of the code. Essentially, it allows the switching of branches  
		*-b <branchName> *- Creates a new branch from the master copy  
		  
		--SAMPLE SCRIPT--  
		*git checkout -b "hotfix" * - creates a new branch of the master-copy called "hotfix"  
		*git commit -am "message" *- Commits any changes you made to the hotfix branch  
		*git checkout master *-switches the working directory to the master-copy  
		*git merge hotfix * - merges the changes from the hotfix branch onto the master branch  
		*git branch -d hotfix *- deletes the branch "hotfix" since it is now merged into the master branch  
  
6) __WORKING TOGETHER via INTERNET__  
  
	Say that someone made changes that you want and they're stored on their repository. You can add a remote and push/pull to that repository.  
	  
	*git remote add <name> <networkAddress> *- Adds a remote onto another computer  
	*git push <remoteName> <branchName> - *Put code somewhere  
	*git pull <remoteName> <branchName> *- Get code from somewhere  
	  
	**The default branchName is always "master"**  
  
  
## GitHub  
  
	**Promotes open-sourceness and allows for easy exchanging of code.**  
	  
	**Fork -** A complete copy of a repository at any specific time. Allows independent development of projects by other people.  
	**Pull request -** A signal sent to the owner of the repository to pull the changes from your repository and put them into the main repository.  
	  
	http://help.github.com/articles/fork-a-repo  
	http://help.github.com/articles/using-pull-requests  
	  
	  
