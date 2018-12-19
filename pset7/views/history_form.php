<table class="table table-striped">
    <thead>
        <tr>
            <td><b>Symbol</b></td>
            <td><b>Shares</b></td>
            <td><b>Price</b></td>
            <td><b>Transacted</b></td>
        </tr>
    </thead>
    <tbody>
        <?php foreach ($transactions as $transaction): ?>
            <tr>
                <td><?= $transaction["symbol"] ?></td>
                <td><?= $transaction["shares"] ?></td>
                <td><?= $transaction["price"] ?></td>
                <td><?= $transaction["transacted"] ?></td>
            </tr>
        <?php endforeach ?>
    </tbody>
</table>