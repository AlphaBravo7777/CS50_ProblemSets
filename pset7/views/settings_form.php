<form action="settings.php" method="post">
    <fieldset>
        <div class="form-group">
            <input autocomplete="off" autofocus class="form-control" name="oldpass" placeholder="Old password" type="password"/>
        </div>
        <div class="form-group">
            <input class="form-control" name="newpass" placeholder="New password" type="password"/>
        </div>
        <div class="form-group">
            <input class="form-control" name="confirmation" placeholder="New password (again)" type="password"/>
        </div>
        <div class="form-group">
            <button class="btn btn-default" type="submit">
                <span aria-hidden="true" class="glyphicon glyphicon-log-in"></span>
                Update
            </button>
        </div>
    </fieldset>
</form>