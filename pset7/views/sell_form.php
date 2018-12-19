<form action="sell.php" method="post">
    <div class="form-group">
        <select class="form-control" name="symbol">
            <option disabled selected value="">Symbol</option>
            <?php foreach ($symbols as $symbol): ?>
                <option value=<?= $symbol ?>><?= $symbol ?></option>
            <?php endforeach ?>
        </select>
    </div>
    <div class="form-group">
        <input autocomplete="off" autofocus class="form-control" min="0" name="shares" placeholder="Shares" type="number">
    </div>
    <button class="btn btn-primary" type="submit">Sell</button>
</form>