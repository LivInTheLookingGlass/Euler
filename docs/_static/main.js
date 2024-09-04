$(document).ready(function() {
    $('table.datatable').DataTable({
        columnDefs: [{ width: 'auto', targets: '_all' }],
        paging: false,
        searching: false,
    });
});
